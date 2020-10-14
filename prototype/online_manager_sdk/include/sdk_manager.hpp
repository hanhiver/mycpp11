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
    SUCCESS = 0,                  // 调用成功
    INVALID_CONFIG_FILE = -1,     // 配置文件错误
    INVALID_PUBLIC_KEY = -2,      // 公钥错误
    AUTH_EXPIRED = -3,            // 鉴权过期
    FAILED_CONNECT_SERVER = -4,   // 联系服务器失败
    UNKNOW_ERROR = -199,          // 其他未知错误
};

class SDKManager
{
public:
    /**
     * @brief 获取SDKManager实例
     *
     * @retval 单例的SDKManager实例
     */
    static SDKManager& Get();

    /**
     * @brief SDKManager初始化
     * @param config_file_path 客户端配置文件，全路径或者相对路径
     *
     * @retval 初始化结果，参考AUTH_CODE
     */
    AUTH_CODE Init(const std::string& config_file_path);

    /**
     * @brief 调用函数查询当前鉴权状态
     *
     * @retval true表示当前鉴权有效，false表示鉴权过期
     */
    bool Auth(); 

    /**
     * @brief 记录函数的成功调用次数
     * @param func_name 函数名称字符串
     * @param call_count 本次记录成功的调用次数
     *
     */
    void Count(const std::string func_name, unsigned int call_count);

    /**
     * @brief 关闭SDKManager
     */
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
