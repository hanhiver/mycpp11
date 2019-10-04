#include <iostream>
#include <future> 

void helloThread(int i)
{
    std::cout << "Hello from thread. " << i << std::endl;
}

struct sayHello
{
    int operator()(int s)
    {
        std::cout << "Hello, " << s << std::endl;
        return 0;
    }
};

int main()
{
    helloThread(2);
    std::packaged_task<void(int)> t1(helloThread);
    t1(2);
    
    sayHello sh = sayHello();
    sh(5);

    std::packaged_task<int(int)> t2(sh);
    t2(5);
    /*
    std::future<int> f = task.get_future();
    std::thread th(std::move(task), "dhan");
    th.join();
    */
    //t2(str);
    
    //sayHello()("dhan");

    return 0;
}