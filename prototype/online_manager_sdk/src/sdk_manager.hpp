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

#include "timer.hpp"

#include <iostream> 
#include <unordered_map>
#include <mutex> 
#include <atomic> 
#include <thread> 

class SDKManager
{
public:
    static SDKManager& Get();
    void Init(const std::string config_filepath);
    bool Auth(); 
    bool Count(const std::string func_name, unsigned int call_count);
    void Shutdown();

private:
    SDKManager();
    SDKManager(const SDKManager&);
    ~SDKManager();
    class SDKManagerImpl;
    SDKManagerImpl *impl; 
};

class SDKManager::SDKManagerImpl
{
private:
    unsigned int countDown; 
    bool auth_status; 
}