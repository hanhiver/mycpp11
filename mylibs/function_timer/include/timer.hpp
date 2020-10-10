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
    
    void start_timer(int interval, std::function<void()> task);
    void start_once(int delay, std::function<void()> task);
    void stop_timer();

private:
    std::atomic<bool> _expired;
    std::atomic<bool> _try_to_expire; 
    std::mutex _mutex; 
    std::condition_variable _expired_cond; 
};

