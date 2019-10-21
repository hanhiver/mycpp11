#pragma once 
#ifndef THREAD_POOL
#define THREAD_POOL 

#include <vector> 
#include <queue>
#include <thread> 
#include <atomic> 
#include <condition_variable> 
#include <future> 
#include <functional> 
#include <stdexcept> 

namespace std
{
#define MAX_THREAD_NUM 256 

class thread_pool
{
    using Task = std::function<void()>;

    std::vector<std::thread> pool; 
    std::queue<Task> tasks; 

    std::mutex m_lock; 
    std::condition_variable cv_task; 
    std::atomic<bool> stopped; 
    std::atomic<int> idlThrNum; 

public: 
    inline thread_pool(unsigned short size = 4) : stopped(false)
    {
        idlThrNum = size<1 ? 1 : size; 
        
        for (size=0; size<idlThrNum; ++size)
        {
            pool.emplace_back([this]
            {
                while(!this->stopped)
                {
                    std::function<void()> task; 
                    
                    {
                        std::unique_lock<std::mutex> lock(this->m_lock);
                        this->cv_task.wait(lock, [this]
                        {
                            return this->stopped.load() || !this->tasks.empty();
                        }); 

                        if (this->stopped && this->tasks.empty())
                        {
                            return; 
                        }
                        
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    idlThrNum--; 
                    task();
                    idlThrNum++; 
                }
            });
        }
    }

    inline ~thread_pool()
    {
        stopped.store(true);
        cv_task.notify_all(); 
        for (std::thread& thread : pool)
        {
            if thread.joinable()
            {
                thread.join();
            }
        }
    }

    template<typename F, typename... Args>
    
};


}

#endif