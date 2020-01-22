#include <iostream> 
#include <boost/coroutine2/all.hpp>

void foo(boost::coroutines2::coroutine<void>::push_type& sink)
{
    std::cout << "a = ";
    sink();
    std::cout << "b = ";
    sink();
    std::cout << "c = "; 
}

int main()
{
    boost::coroutines2::coroutine<void>::pull_type source(foo);
    std::cout << "1" << std::endl;
    source();
    std::cout << "2" << std::endl;
    source();
    std::cout << "3" << std::endl;

    return 0;
}
