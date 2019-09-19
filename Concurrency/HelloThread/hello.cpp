#include <iostream>
#include <thread> 

void hello()
{
    std::cout << "Hello! Concurrency!" << std::endl;
}

class background_hello
{
public:
    void operator() () const 
    {
        std::cout << "Hello in background_hello!" << std::endl;
    }
};

int main()
{
    std::thread t1(hello);
    t1.join();

    background_hello bh; 
    std::thread t2(bh);
    t2.join();

    // Below shows the detach termination. 
    std::thread ta(hello);
    std::thread tb = std::move(t1);
    ta = std::thread(bh);
    ta = std::thread(hello); // Oops, terminate() will be called. 
}