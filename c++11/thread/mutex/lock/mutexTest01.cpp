#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void print_thread_id_mtx(int id)
{
    mtx.lock();
    std::cout << "Thread # " << id << std::endl;
    mtx.unlock();
}

void print_thread_id(int id)
{
    std::cout << "Thread # " << id << std::endl;
}

int main()
{
    std::thread threads[10];
    
    std::cout << "Test without mutex lock." << std::endl;

    for (int i=0; i<10; ++i)
    {
        threads[i] = std::thread(print_thread_id, i+1);
    }

    for (auto& th : threads)
    {
        th.join();
    }

    std::cout << "\n\nTest the threads with mutex." << std::endl;

    for (int i=0; i<10; ++i)
    {
        threads[i] = std::thread(print_thread_id_mtx, i+1);
    }

    for (auto& th : threads)
    {
        th.join();
    }

    return 0;
}

