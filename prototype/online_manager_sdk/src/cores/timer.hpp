/**
 *  C++定时器模块
 *  Copyright (C) 2020 Alibaba Dong HAN
 *  
 *  This file is part of public tools class for the sdk online manager project. 
 *                                                                            
 *  @file     timer.hpp
 *  @brief    基于C++11的定时器模块
 *  基于C++11的定时器模块，可以按照既定时间点执行任务
 *                                                                            
 *  @author   Dong Han @ Alibaba
 *  @email    hd275562@alibaba-inc.com
 *  @version  1.0.0.1
 *  @date     2020.10.09
 *
 */

#ifndef DAMO_SDK_ONLINE_MANAGER_TIMER_HPP
#define DAMO_SDK_ONLINE_MANAGER_TIMER_HPP

#include <functional>
#include <chrono>
#include <thread> 
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>

class Timer
{
public:
    Timer();
    Timer(const Timer& timer);
    ~Timer();
    
    /** 
     * @brief 启动周期定时器
     * @param interval 指定的运行时间周期（毫秒）
     * @param task     定时时间执行的任务
     *
     * @return 无
     */
    void StartTimer(int interval, std::function<void()> task);

    /** 
     * @brief 启动单次定时器
     * @param interval 指定的运行的延迟时间（毫秒）
     * @param task     定时时间执行的任务
     *
     * @return 无
     */
    void StartOnce(int delay, std::function<void()> task);

    /** 
     * @brief 停止计时器的运行
     *
     * @return 无
     */
    void StopTimer();

private:
    std::atomic<bool> mExpired;
    std::atomic<bool> mTryToExpire; 
    std::mutex mMutex; 
    std::condition_variable mExpiredCond; 
};

#endif   // DAMO_SDK_ONLINE_MANAGER_TIMER_HPP