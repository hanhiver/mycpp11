#include "timer.hpp"

Timer::Timer(): mExpired(true), mTryToExpire(false)
{}

Timer::Timer(const Timer& timer)
{
    mExpired = timer.mExpired.load();
    mTryToExpire = timer.mTryToExpire.load();
}

Timer::~Timer()
{
    StopTimer();
}

void Timer::StartTimer(int interval, std::function<void()> task)
{
    // 如果timer已经启动，避免二次启动。
    if (mExpired == false)
    {
        return; 
    }

    // 启动一个异步的计时器，生成一个新的线程并等待。
    mExpired = false;
    std::thread([this, interval, task]()
    {
        while (!mTryToExpire)
        {
            // 线程睡眠interval时间然后执行task，直到计时器停止。
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            task();
        }

        {
            // 计时器需要停止，更新条件变量，唤醒主线程。
            std::lock_guard<std::mutex> locker(mMutex);
            mExpired = true;
            mExpiredCond.notify_one();
        }
    }).detach();
}

void Timer::StartOnce(int delay, std::function<void()> task)
{
    std::thread([delay, task]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        task();
    }).detach();
}

void Timer::StopTimer()
{
    // 已经停止就不要再次停止。
    if (mExpired)
    {
        return;
    }

    if (mTryToExpire)
    {
        return;
    }

    // 等待倒计时终止。
    mTryToExpire = true;
    {
        std::unique_lock<std::mutex> locker(mMutex);
        mExpiredCond.wait(locker, [this]()
        {
            return mExpired == true;
        });

        // 重置计时器状态。
        if (mExpired = true)
        {
            mTryToExpire = false;
        }
    }
}

