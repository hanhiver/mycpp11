#include <iostream> 
#include <thread> 
#include <future> 
#include <atomic>
#include <vector> 
#include <chrono>

#include "../threadsafe_queue.cpp"

class threads_joiner
{
private: 
    std::vector<std::thread>& vect;

public: 
    threads_joiner(std::vector<std::thread>& vect_) : vect(vect_)
    {}

    ~threads_joiner()
    {
        for (auto& thread : vect)
        {
            if (thread.joinable())
                thread.join();
        }
    }
};

class thread_pool
{
private:
    std::atomic_bool done; 
    threadsafe_queue<std::function<void()>> work_queue; 
    std::vector<std::thread> threads; 
    threads_joiner joiner;

    void work_thread()
    {
        while(!done)
        {
            std::function<void()> task; 
            if (work_queue.try_pop(task))
            {
                task();
            }
            else
            {
                std::this_thread::yield();
            }
        }
    }

public:
    thread_pool() : done(false), joiner(threads)
    {
        unsigned const thread_count = std::thread::hardware_concurrency();

        try
        {
            for (unsigned i=0; i<thread_count; ++i)
            {
                threads.push_back(std::thread(&thread_pool::work_thread, this));
            }
        }
        catch(...)
        {
            done = true; 
            throw; 
        }
    }

    ~thread_pool()
    {
        done = true; 
    }

    template<typename FunctionType>
    void submit(FunctionType f)
    {
        work_queue.push(std::function<void()>(f));
    }
};

void sayHello()
{
    std::cout << "Hello from " << std::this_thread::get_id() << std::endl; 
} 

int main()
{
    unsigned long const TASK_NUM = 10;
    thread_pool tpool; 
    
    for (unsigned long i=0; i<TASK_NUM; ++i)
    {
        tpool.submit(sayHello);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0; 
}
