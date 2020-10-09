/**
 *  基于protobuf的客户端配置文件读取类
 *  Copyright (C) 2020 Alibaba Dong HAN
 *  
 *  This file is part of public tools class for the sdk online manager project. 
 *                                                                            
 *  @file     params.hpp
 *  @brief    客户端配置文件读取工具类
 *  在sdk_online_manager项目中的客户端读取配置文件的辅助工具类
 *                                                                            
 *  @author   Dong Han @ Alibaba
 *  @email    hd275562@alibaba-inc.com
 *  @version  1.0.0.0
 *  @date     2020.10.09
 *
 */

#ifndef DAMO_SDK_ONLINE_MANAGER_PARAMS_HPP
#define DAMO_SDK_ONLINE_MANAGER_PARAMS_HPP

#include <vector> 
#include <algorithm>
#include <fstream> 
#include <string> 

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <fcntl.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "config.pb.h"

/**
 * @brief 参数集合 \n
 * 提供对于指定格式的配置文件读取然后生成参数供程序各个部分获取的类型
 */
class Params
{
public: 
    /** 
     * @brief 获取参数单例类型入口
     *
     * @return 返回单例类型参数
     */
    static Params& Get()
    {
        static Params instance; 
        return instance; 
    }

    /** 
     * @brief 从指定的配置文件中读取参数
     * @param filepath  指定的配置文件
     *
     * @return 返回是否成功读取配置文件。
     */
    bool ParaseParamsFile(std::string filepath);

    /** 
     * @brief 获取SystemParams的读取入口
     *
     * @return 返回SystemParams的配置读取入口
     */
    inline static const sdk_online_manager::SystemParams& GetSystemParams()
    {
        return mParams.sys_params();
    }

    /** 
     * @brief 获取KeyInfo的读取入口
     *
     * @return 返回KeyInfo的配置读取入口
     */
    inline static const sdk_online_manager::KeyInfo& GetKeyInfo()
    {
        return mParams.key_info();
    }
    
    /** 
     * @brief 打印出读取到的配置信息
     *
     */
    void PrintParams();

private: 
    Params() {}
    static sdk_online_manager::ClientParams mParams; 
};

#endif  // DAMO_SDK_ONLINE_MANAGER_PARAMS_HPP