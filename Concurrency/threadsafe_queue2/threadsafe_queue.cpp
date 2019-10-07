#include <queue> 
#include <mutex> 
#include <condition_variable> 
#include <memory> 
#include <string> 
#include <atomic> 
#include <mutex> 

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

    // (1). 没有调用termination的时候，每调用一次，出队一个元素，直到队列为空，阻塞调用线程。 
    // (2). 调用了termination之后，本方法永不阻塞，如果原本已经处于阻塞状态，接触阻塞。
    // (3). 返回true时，value值有效；返回false时，value值无效。调用了termination且队列为空的时候返回false. 
    bool wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut);
        
        data_cond.wait(lk, [this] 
        {
            return ((!data_queue.empty()) || m_bTermination);
        });

        // 如果队列不是空的，出队一个元素。 
        if (!data_queue.empty())
        {
            value = std::move(*data_queue.front());
            data_queue.pop();
            return true; 
        }
        // 队列为空则返回失败。
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

    // 设置队列为退出状态。 
    // 在退出状态下，忽略入队，可以执行出队。 但是当队列为空的时候，wait_and_pop不再阻塞。
    void termination()
    {
        std::lock_guard<std::mutex> lk(mut);
        m_bTermination = true; 
        data_cond.notify_all();
    }

    // 是否为退出状态。 
    bool is_termination()
    {
        return m_bTermination;
    }
};