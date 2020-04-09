#ifndef THREADS_POOL_DHAN
#define THREADS_POOL_DHAN

#include <iostream> 
#include <vector> 
#include <queue> 
#include <chrono>
#include <memory> 
#include <string> 

#include <mutex> 
#include <thread> 
#include <future> 
#include <atomic>
#include <condition_variable> 

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

template<typename T> 
class threadsafe_queue
{
private: 
    mutable std::mutex mut; 
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
    std::atomic<bool> m_bTermination; 

public: 
    threadsafe_queue() : m_bTermination(false)
    {}

    ~threadsafe_queue(void)
    {}

    bool wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut);
        
        data_cond.wait(lk, [this] 
        {
            return ((!data_queue.empty()) || m_bTermination);
        });

        if (!data_queue.empty())
        {
            value = std::move(*data_queue.front());
            data_queue.pop();
            return true; 
        }

        return false;
    }

    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
        {
            return false; 
        }

        value = std::move(*data_queue.front());
        data_queue.pop();
        return true; 
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{
            return ((!data_queue.empty()) || m_bTermination);
        });
        if (!data_queue.empty())
        {
            std::shared_ptr<T> res = data_queue.front();
            data_queue.pop();
            return res; 
        }
        return nullptr; 
    }

    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
        {
            return nullptr; 
        }
        std::shared_ptr<T> res = data_queue.front();
        data_queue.pop();
        return res; 
    }

    void push(T new_value)
    {
        if (m_bTermination)
        {
            return; 
        }
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one(); 
    }

    bool empty() const 
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }

    int size()
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.size();
    }

    void termination()
    {
        std::lock_guard<std::mutex> lk(mut);
        m_bTermination = true; 
        data_cond.notify_all();
    }

    bool is_termination()
    {
        return m_bTermination;
    }
};

class threads_pool
{
private:
    std::atomic_bool done; 
    std::atomic_bool ready; 
    threadsafe_queue<std::function<void()>> work_queue; 
    std::vector<std::thread> threads; 
    threads_joiner joiner;

    void work_thread()
    {
        while(!done)
        {
            if (!ready)
            {
                ready = true; 
            }
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
    threads_pool(int pool_size) : done(false), joiner(threads), ready(false)
    {
        if (pool_size <= 0)
        {
            pool_size = std::thread::hardware_concurrency()/2;
        }
        unsigned const thread_count = pool_size;

        try
        {
            for (unsigned i=0; i<thread_count; ++i)
            {
                threads.push_back(std::thread(&threads_pool::work_thread, this));
            }
        }
        catch(...)
        {
            done = true; 
            throw; 
        }

        while (!ready)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }

    ~threads_pool()
    {
        done = true; 
    }

    template<typename FunctionType>
    void submit(FunctionType f)
    {
        work_queue.push(std::function<void()>(f));
    }

    bool queue_empty() const
    {
        return work_queue.empty();
    }
};

#endif //THREADS_POOL_DHAN
