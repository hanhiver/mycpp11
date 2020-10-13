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

#ifndef DAMO_SDK_ONLINE_MANAGER_SDK_MANAGER_HPP
#define DAMO_SDK_ONLINE_MANAGER_SDK_MANAGER_HPP

#include <string> 
#include <memory>

//namespace SDKManager
//{
enum AUTH_CODE
{
    SUCCESS = 0,
    INVALID_CONFIG_FILE = -1, 
    INVALID_PUBLIC_KEY = -2,
    AUTH_EXPIRED = -3, 
    FAILED_CONNECT_SERVER = -4,
    UNKNOW_ERROR = -199,
};

class SDKManager
{
public:
    static SDKManager& Get();
    AUTH_CODE Init(const std::string& config_file_path);
    AUTH_CODE Auth(); 
    void Count(const std::string func_name, unsigned int call_count);
    void Shutdown();

private:
    SDKManager(); 
    ~SDKManager();
    SDKManager(const SDKManager&);
    class SDKManagerImpl;
    std::shared_ptr<SDKManagerImpl> mImpl;
};

//} // namespace SDKManager
#endif  // DAMO_SDK_ONLINE_MANAGER_SDK_MANAGER_HPP
