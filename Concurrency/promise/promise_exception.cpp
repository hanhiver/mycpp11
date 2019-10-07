#include <iostream> 
#include <future> 
#include <thread> 
#include <exception> // std::make_exception_ptr
#include <stdexcept> // std::logic_error

void catch_error(std::future<void>& future)
{
    try
    {
        future.get();
    }
    catch(std::logic_error& e)
    {
        std::cerr << "logic_err: " << e.what() << std::endl;
    }
}

int main()
{
    std::promise<void> promise;
    std::future<void> future = promise.get_future();

    std::thread thread(catch_error, std::ref(future));

    // 自定义异常需要用make_exception_ptr转换。
    promise.set_exception(std::make_exception_ptr(std::logic_error("caught")));

    thread.join();
    return 0;
}