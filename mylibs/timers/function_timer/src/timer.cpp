#include "timer.hpp"

Timer::Timer(): _expired(true), _try_to_expire(false)
{}

Timer::Timer(const Timer& timer)
{
    _expired = timer._expired.load();
    _try_to_expire = timer._try_to_expire.load();
}

Timer::~Timer()
{
    stop_timer();
}

void Timer::start_timer(int interval, std::function<void()> task)
{
    // 如果timer已经启动，避免二次启动。
    if (_expired == false)
    {
        return; 
    }

    // 启动一个异步的计时器，生成一个新的线程并等待。
    _expired = false;
    std::thread([this, interval, task]()
    {
        while (!_try_to_expire)
        {
            // 线程睡眠interval时间然后执行task，直到计时器停止。
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            task();
        }

        {
            // 计时器需要停止，更新条件变量，唤醒主线程。
            std::lock_guard<std::mutex> locker(_mutex);
            _expired = true;
            _expired_cond.notify_one();
        }
    }).detach();
}

void Timer::start_once(int delay, std::function<void()> task)
{
    std::thread([delay, task]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        task();
    }).detach();
}

void Timer::stop_timer()
{
    // 已经停止就不要再次停止。
    if (_expired)
    {
        return;
    }

    if (_try_to_expire)
    {
        return;
    }

    // 等待倒计时终止。
    _try_to_expire = true;
    {
        std::unique_lock<std::mutex> locker(_mutex);
        _expired_cond.wait(locker, [this]()
        {
            return _expired == true;
        });

        // 重置计时器状态。
        if (_expired = true)
        {
            _try_to_expire = false;
        }
    }
}

