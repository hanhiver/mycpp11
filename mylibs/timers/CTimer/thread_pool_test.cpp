#include <iostream> 
#include "thread_pool.h"

void fun(int n)
{
    std::cout << "n : " << n << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void work()
{
    static const int LEN = 100;

    ThreadPool pool(4, true, 10);
    
    int n = 5;
    pool.Submit(fun, n);
    
    std::cout << "n : " << n << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    pool.Submit(fun, 1);
    
    pool.Close();

    pool.Start();

    std::future<void> fu[LEN];
    for (int i = 0; i < LEN; i++)
    {
        fu[i] = pool.Submit(fun, i);
    }
    
    for (int i = 0; i < LEN; fu[i++].wait()) {}
    pool.Close();
}

int main()
{
    work();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}