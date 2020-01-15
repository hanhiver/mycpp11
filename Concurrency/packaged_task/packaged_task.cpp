#include <iostream>
#include <future> 
#include <string> 

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

int returnTask(std::string str)
{
    std::cout << "Return 1, msg: " << str << std::endl;
    return 1; 
}

int main()
{
    helloThread(2);
    std::packaged_task<void(int)> t1(helloThread);
    t1(2);
    
    sayHello sh = sayHello();
    sh(5);

    std::packaged_task<int(int)> t2(sh);
    t2(5);
    
    std::packaged_task<int(std::string)> task(returnTask);
    std::future<int> f = task.get_future();
    task("dhan");
    //std::thread th(std::move(task), "dhan");
    //th.join();
    
    //t2(str);
    
    //sayHello()("dhan");

    return 0;
}