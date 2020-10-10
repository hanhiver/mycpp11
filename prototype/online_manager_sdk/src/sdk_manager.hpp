/**
 *  SDK Online Manager
 *  Copyright (C) 2020 Alibaba Dong HAN
 *  提供在线SDK鉴权下发和调用量统计功能
 *  
 *  This file is part of public tools class for the sdk online manager project. 
 *                                                                            
 *  @file     sdk_manager.hpp
 *  @brief    提供在线SDK鉴权下发和调用量统计功能
 *  在sdk_online_manager项目提供给客户的调用头文件，封装了SDK通过在线获取鉴权和汇报调用统计功能。
 *                                                                            
 *  @author   Dong Han @ Alibaba
 *  @email    hd275562@alibaba-inc.com
 *  @version  1.0.0.0
 *  @date     2020.10.09
 *
 */


#include <string> 
#include <memory>

#include <iostream> 
#include <unordered_map>
#include <mutex> 
#include <atomic> 
#include <thread> 

#include "timer.hpp"
#include "params.hpp"

void hello()
{
    std::cout << "Hello! " << std::endl; 
}
class SDKManager
{
public:
    static SDKManager& Get();

    void Init(const std::string config_filepath);
    bool Auth(); 
    void Count(const std::string func_name, unsigned int call_count);
    void Shutdown();

private:
    SDKManager(); 
    ~SDKManager();
    SDKManager(const SDKManager&);
    class SDKManagerImpl;
    SDKManagerImpl* mImpl; 
};

class SDKManager::SDKManagerImpl
{
public:
    void ConnectServer();
    void HouseKeeping();

    bool GetAuthStatus();
    void SetAuthStatus(bool status);
    void CountUsage(const std::string func_name, unsigned int call_count = 1);
    void ResetCountdown(unsigned int countdown_tick);

    Timer timer; 
    std::mutex mMutex; 
    std::unordered_map<std::string, unsigned int> mSDKCallStatus;
    
    unsigned int mCountDown; 
    unsigned int mRetryTime;
    std::atomic<bool> mAuthValid; 
};

SDKManager& SDKManager::Get()
{
    static SDKManager instance;
    return instance;
}

void SDKManager::Init(const std::string config_filepath)
{
    auto params = Params::Get();
    params.ParaseParamsFile(config_filepath);
    std::cout << "====== Read config file ======" << std::endl;
    params.PrintParams();

    mImpl->mCountDown = params.GetSystemParams().default_report_countdown_time();
    mImpl->mRetryTime = 0; 
    mImpl->mAuthValid = false; 

    mImpl->ConnectServer();
    //mImpl->timer.start_once(mImpl->mCountDown, 
    //    std::bind(&SDKManager::SDKManagerImpl::ConnectServer, *mImpl));
}

bool SDKManager::Auth()
{
    return mImpl->GetAuthStatus();
}

void SDKManager::Count(const std::string func_name, unsigned int call_count)
{
    mImpl->CountUsage(func_name, call_count);
}

void SDKManager::Shutdown()
{
    mImpl->mAuthValid = false;
}

SDKManager::SDKManager()
{
    // C++11 Limitation, chagne to use std::make_unique after C++14. 
    // auto temp_ptr = std::unique_ptr<SDKManagerImpl>();
    // mImpl = std::move(temp_ptr);
    mImpl = new SDKManagerImpl;
    mImpl->mCountDown = 0;
    mImpl->mRetryTime = 0;
    mImpl->mAuthValid = false;
}

SDKManager::~SDKManager()
{
    mImpl->mAuthValid = false; 
    delete mImpl;
}

void SDKManager::SDKManagerImpl::ConnectServer()
{
    std::cout << "Connecting the server. " << std::endl;
    timer.StartTimer(mCountDown*1000, &hello);
    //timer.StartOnce(mCountDown*1000, std::bind(&SDKManager::SDKManagerImpl::ConnectServer, *this));
}

void SDKManager::SDKManagerImpl::HouseKeeping()
{
    std::cout << "House keeping. " << std::endl;
}

bool SDKManager::SDKManagerImpl::GetAuthStatus()
{
    return mAuthValid.load();
}

void SDKManager::SDKManagerImpl::SetAuthStatus(bool status)
{
    mAuthValid.store(status);
}

void SDKManager::SDKManagerImpl::CountUsage(std::string func_name, unsigned int call_count)
{
    std::cout << "Count usage of: " << func_name << " increased " << call_count << std::endl;
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mSDKCallStatus[func_name] += call_count;
    }
}

void SDKManager::SDKManagerImpl::ResetCountdown(unsigned int countdown_tick)
{
    mCountDown = countdown_tick;
}
