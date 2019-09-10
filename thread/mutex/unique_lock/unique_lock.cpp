#include <iostream>
#include <thread>
#include <mutex> 

std::mutex mtx;

void print_thread_id(int id)
{
    std::unique_lock<std::mutex> lck(mtx, std::defer_lock);
    lck.lock();
    std::cout << "Thread #" << id << std::endl;
    lck.unlock();
}

int main()
{
    std::thread threads[10];

    for (int i=0; i<10; ++i)
    {
        threads[i] = std::thread(print_thread_id, i+1);
    }

    for (auto& th : threads)
    {
        th.join();
    }
    
    return 0;
}