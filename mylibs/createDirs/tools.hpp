/**
 *  项目中的各类工具函数
 *  Copyright (C) 2020 Alibaba Dong HAN
 *  
 *  This file is part of public tools class for the sdk online manager project. 
 *                                                                            
 *  @file     tools.hpp
 *  @brief    项目中需要使用的各种工具函数
 *  项目中需要使用的各种可复用的工具函数。
 *                                                                            
 *  @author   Dong Han @ Alibaba
 *  @email    hd275562@alibaba-inc.com
 *  @version  1.0.0.1
 *  @date     2020.10.21
 *
 */

#ifndef DAMO_SDK_ONLINE_MANAGER_TOOLS_HPP
#define DAMO_SDK_ONLINE_MANAGER_TOOLS_HPP

#ifdef WIN32
#include <io.h>
#include <direct.h> 
#else // LINUX or others
#include <unistd.h>
#include <sys/stat.h>
#endif

#include <stdint.h>
#include <string>
#include <sstream>

#ifdef WIN32
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#define MKDIR(path) _mkdir(path)
#else
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#define MKDIR(path) mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

/** 
 * @brief 按照给定路径创建整个目录结构
 * @param dir_path 指定目录全路径
 *
 * @return 无
 *    -<em>0</em> 创建目录成功
 *    -<em>not 0</em> 创建目录失败，返回值为失败error code.
 * 
 * @note 从左到右依次判断文件夹是否存在，不存在就创建
 *       example： /tmp/a/b/c
 *       注意：最后一个如果是文件夹的话,需要加上 '\' 或者 '/'。比如上述例子中的c不会被创建
 */
int32_t createDirs(const std::string& dir_path);

#endif  // DAMO_SDK_ONLINE_MANAGER_TOOLS_HPP