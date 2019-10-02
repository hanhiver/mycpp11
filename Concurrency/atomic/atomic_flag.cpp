#include <iostream> 
#include <atomic> 
#include <vector> 
#include <thread>

class spinlock_mutex
{
    std::atomic_flag flag; 

public:
    spinlock_mutex(): flag(ATOMIC_FLAG_INIT)
    {}

    void lock()
    {
        while(flag.test_and_set(std::memory_order_acquire));
    }

    void unlock()
    {
        flag.clear(std::memory_order_release);
    }
};

void increase(int& num)
{
    for (int i=0; i<1000; ++i)
    {
        ++num;
    } 
}

void increase_lock(spinlock_mutex& lock, int& num)
{   
    for (int i=0; i<1000; ++i)
    {
        lock.lock();
        ++num;
        lock.unlock();
    } 
}

int main()
{
    std::cout << "Test without lock: " << std::endl;

    std::vector<std::thread> threads; 
    int num = 0;
    for (int i=0; i<8; ++i)
    {
        std::thread th(increase, std::ref(num));
        threads.push_back(std::move(th));
    }
    for (auto &th : threads)
    {
        th.join();
    }
    std::cout << "Num: " << num << std::endl; 

    std::cout << "Test with my lock: " << std::endl;
    threads.clear(); 
    spinlock_mutex mylock; 
    num = 0;
    for (int i=0; i<8; ++i)
    {
        std::thread th(increase_lock, std::ref(mylock), std::ref(num));
        threads.push_back(std::move(th));
    }
    for (auto &th : threads)
    {
        th.join();
    }
    std::cout << "Num: " << num << std::endl; 
    
}   