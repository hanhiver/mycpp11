#include <iostream>
#include <thread> 

class thread_guard
{
    std::thread& t; 

public:
    explicit thread_guard(std::thread& t_): t(t_)
    {}

    ~thread_guard()
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};


void hello()
{
    std::cout << "Hello! Concurrency!" << std::endl;
}

int main()
{
    std::thread t(hello);
    thread_guard g(t);
}