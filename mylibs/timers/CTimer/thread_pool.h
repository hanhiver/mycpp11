#include <functional>
#include <thread>
#include <vector>
#include <queue>
#include <future>
#include <cassert>
#include <algorithm>

#include "mutex_obj.hpp"
#include "event.hpp"


class ThreadPool
{
    typedef std::function<void()> Task;
    typedef std::queue<Task> TaskQueue;
    typedef std::shared_ptr<std::thread> ThreadPtr;
    typedef std::vector<ThreadPtr> Pool;

public:
    ThreadPool(size_t coreCnt = 1, bool expand = false, size_t maxCnt = std::thread::hardware_concurrency())
        : coreCnt(coreCnt), expand(coreCnt ? expand : true), maxCnt(maxCnt), run(true)
    {
    }

    ~ThreadPool()
    {
        Close();
    }

    void Start()
    {
        run = true;
        event.Reset();
    }

    void Close()
    {
        run = false;
        event.NotifyAll();
        Pool vec;
        do
        {
            MUTEXOBJECT_LOCK_GUARD(pool);
            vec = pool.Data();
        }
        while (false);

        std::for_each(std::begin(vec), std::end(vec), [] (const ThreadPtr & it)
        {
            if (it->joinable())
            {
                if (std::this_thread::get_id() == it->get_id())
                    it->detach();
                else
                    it->join();
            }
        });
    }

    template<typename Fun, typename... Args>
    std::future< typename std::result_of<Fun(Args...)>::type > Submit(Fun && fun, Args&&... args)
    {
        if (!run.load())
            throw std::runtime_error("ThreadPool has closed!");

        typedef typename std::result_of<Fun(Args...)>::type ReturnType;
        auto task = std::make_shared< std::packaged_task<ReturnType()> >
                    (std::bind(std::forward<Fun>(fun), std::forward<Args>(args)...));

        do
        {
            MUTEXOBJECT_LOCK_GUARD(taskQueue);
            taskQueue->emplace([task] ()
            {
                (*task)();
            });
        }
        while (false);

        event.NotifyOne();

        if (NeedNewThread())
        {
            NewThread();
        }
        
        return task->get_future();
    }

private:
    bool NeedNewThread()
    {
        do
        {
            MUTEXOBJECT_LOCK_GUARD(pool);
            if (pool->empty())
                return true;
            if (pool->size() == maxCnt)
                return false;
        }
        while (false);

        do
        {
            MUTEXOBJECT_LOCK_GUARD(taskQueue);
            return taskQueue->size() > 0;
        }
        while (false);

        assert(false);
    }

    void NewThread()
    {
        MUTEXOBJECT_LOCK_GUARD(pool);
        if (pool->size() < coreCnt)
            pool->emplace_back(new std::thread(std::bind(&ThreadPool::Dispath, this, true)));
        else if (expand)
            pool->emplace_back(new std::thread(std::bind(&ThreadPool::Dispath, this, false)));
    }

    void Dispath(bool core)
    {
        while (run.load())
        {
            if (Task task = PickOneTask())
                task();
            else if (!event.WaitFor(std::chrono::minutes(1)) && !core)
            {
                KillSelf();
                break;
            }
        }
    }

    void KillSelf()
    {
        MUTEXOBJECT_LOCK_GUARD(pool);
        auto it = std::find_if(std::begin(pool.Data()), std::end(pool.Data()), [] (const ThreadPtr & it)
        {
            return std::this_thread::get_id() == it->get_id();
        });

        (*it)->detach();
        pool->erase(it);
    }

    Task PickOneTask()
    {
        MUTEXOBJECT_LOCK_GUARD(taskQueue);
        Task ret = nullptr;
        if (!taskQueue->empty())
        {
            ret = std::move(taskQueue->front());
            taskQueue->pop();
        }
        return ret;
    }

private:
    MutexObject<Pool> pool;
    MutexObject<TaskQueue> taskQueue;
    Event event;

    size_t coreCnt;
    bool expand;
    size_t maxCnt;
    std::atomic<bool> run;
};