#include <iostream> 
#include <atomic>
#include <thread> 
#include <future> // std::future; 
#include <map> // std::map

#include "../threadsafe_queue.cpp"

class function_wrapper
{
    struct impl_base
    {
        virtual void call() = 0;
        virtual ~impl_base() {}
    };

    std::unique_ptr<impl_base> impl; 
    
    template<typename F>
    struct impl_type: impl_base
    {
        F f; 
        impl_type(F&& f_): f(std::move(f_)) 
        {}
        
        void call()
        {
            f(); 
        }
    };

public: 
    template<typename F> 
    function_wrapper(F&& f): impl(new impl_type<F>(std::move(f))) 
    {}

    void operator()() 
    {
        impl->call();
    }

    function_wrapper() = default; 
    
    function_wrapper(function_wrapper&& other): impl(std::move(other.impl))
    {}

    function_wrapper& operator=(function_wrapper&& other)
    {
        impl = std::move(other.impl);
        return *this; 
    }

    function_wrapper(const function_wrapper&) = delete; 
    function_wrapper(function_wrapper&) = delete; 
    function_wrapper& operator=(const function_wrapper&) = delete; 

};

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
    std::atomic<bool> done; 
    std::atomic<bool> ready; 
    std::vector<std::thread> threads; 
    threads_joiner joiner; 
    threadsafe_queue<function_wrapper> work_queue; 
    
    void worker_thread()
    {
        if (!ready)
        {
            ready = true; 
        }

        while (!done)
        {
            function_wrapper task; 
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
    thread_pool(): done(false), ready(false), joiner(threads)
    {
        unsigned const threads_num = std::thread::hardware_concurrency();

        try
        {
            for (unsigned i=0; i<threads_num; ++i)
            {
                threads.push_back(std::thread(&thread_pool::worker_thread, this));
            }
        }
        catch(...)
        {
            done = true; 
            throw; 
        }

        while(!ready)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
        
    }

    ~thread_pool()
    {
        done = true; 
    }

    template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f)
    {
        typedef typename std::result_of<FunctionType()>::type result_type; 

        std::packaged_task<result_type()> task(std::move(f));
        std::future<result_type> res(task.get_future());
        work_queue.push(std::move(task));
        return res; 
    }
};

std::thread::id sayHello()
{
    std::cout << "Hello from " << std::this_thread::get_id() << std::endl; 
    return std::this_thread::get_id();
} 

int main()
{
    unsigned long const TASK_NUM = 50;
    std::vector<std::future<std::thread::id>> rvect; 
    thread_pool tpool; 
    
    for (unsigned long i=0; i<TASK_NUM; ++i)
    {
        rvect.push_back(std::move(tpool.submit(sayHello)));
        std::cout << "#" << i << " sbumitted. " << std::endl; 
    }

    std::map<std::thread::id, long> tmap; 
    for (auto& elem : rvect)
    {
        tmap[elem.get()]++; 
    }

    std::cout << "\nResult: " << std::endl; 
    for (auto& elem : tmap)
    {
        std::cout << "Thread <" << elem.first << "> finished " << elem.second << " tasks. " << std::endl; 
    }

    // No need to wait the thread pool finish all task. 
    // In the previous get(), ensure all task finished. 
    
    return 0; 
}