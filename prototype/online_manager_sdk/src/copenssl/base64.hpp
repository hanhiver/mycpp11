/**
 *  Base64 encode and decode tools. 
 *  Copyright (C) 2020 Alibaba Dong HAN
 *  
 *  This file is part of public tools class for the sdk online manager project. 
 *                                                                            
 *  @file     base64.hpp
 *  @brief    base64的编码和解码类
 *  基于C++提供对基础的base64编码和解码支持。
 *                                                                            
 *  @author   Dong Han @ Alibaba
 *  @email    hd275562@alibaba-inc.com
 *  @version  1.0.0.1
 *  @date     2020.10.09
 *
 */

#ifndef DAMO_SDK_ONLINE_MANAGER_BASE64_HPP
#define DAMO_SDK_ONLINE_MANAGER_BASE64_HPP

#include <string>

/** 
 * @brief base64对指定的函数进行编码
 * @param in  输入的待编码字符串
 * @param len 输入带编码字符串的长度
 *
 * @retval base64编码完成的字符串
 */
std::string base64_encode(unsigned char const* in, unsigned int len);

/** 
 * @brief base64对指定的函数进行解码
 * @param s  输入的待解码字符串
 *
 * @retval base64解码后的字符串
 */
std::string base64_decode(std::string const& s);

#endif  // DAMO_SDK_ONLINE_MANAGER_BASE64_HPP