#include <mutex>
#include <condition_variable>

class Event
{
public:
    Event() = default;

    void Wait()
    {
        std::unique_lock<std::mutex> lock(mu);
        con.wait(lock, [this] ()
        {
            return this->flag || this->all;
        });
        if (!all)
            flag = false;
    }

    template <typename _Rep, typename _Period>
    bool WaitFor(const std::chrono::duration<_Rep, _Period> & duration)
    {
        std::unique_lock<std::mutex> lock(mu);
        bool ret = true;
        ret = con.wait_for(lock, duration, [this] ()
        {
            return this->flag || this->all;
        });
        if (ret && !all)
            flag = false;
        return ret;
    }

    template <typename _Clock, typename _Duration>
    bool WaitUntil(const std::chrono::time_point<_Clock, _Duration> & point)
    {
        std::unique_lock<std::mutex> lock(mu);
        bool ret = true;
        ret = con.wait_until(lock, point, [this] ()
        {
            return this->flag || this->all;
        });
        if (ret && !all)
            flag = false;
        return ret;
    }

    void NotifyOne()
    {
        std::lock_guard<std::mutex> lock(mu);
        flag = true;
        con.notify_one();
    }

    void NotifyAll()
    {
        std::lock_guard<std::mutex> lock(mu);
        all = true;
        con.notify_all();
    }

    void Reset()
    {
        std::lock_guard<std::mutex> lock(mu);
        flag = all = false;
    }

private:
    Event(const Event &) = delete;
    Event & operator = (const Event &) = delete;

private:
    bool flag = false;
    bool all = false;

    std::mutex mu;
    std::condition_variable con;
};