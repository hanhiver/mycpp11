#include <iostream> 
#include <chrono>
#include <atomic>

#include "threads_pool.hpp"

void sayHello()
{
    std::cout << "Hello from " << std::this_thread::get_id() << std::endl; 
    std::this_thread::sleep_for(std::chrono::seconds(1));
} 

int main()
{
    std::atomic_int num_tasks;

    unsigned long const TASK_NUM = 30;
    thread_pool tpool(10); 
    
    num_tasks = TASK_NUM;
    for (unsigned long i=0; i<TASK_NUM; ++i)
    {
        tpool.submit([&num_tasks](){
            sayHello();
            -- num_tasks;
        });
    }

    //std::this_thread::sleep_for(std::chrono::seconds(1));
    //while(!tpool.queue_empty())
    while(num_tasks>0)
    {
        std::this_thread::yield();
    }

    return 0; 
}
