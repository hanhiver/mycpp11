/**
 *  包装openssl类库，支持C++方式调用加密解密签名鉴权的各个功能。
 *  Copyright (C) 2020 Alibaba Dong HAN
 *  
 *  This file is part of public tools class for the sdk online manager project. 
 *                                                                            
 *  @file     COpenSSL.hpp
 *  @brief    提供加密解密签名鉴权各项服务功能。
 *  使用C++包装openssl类库，提供对于信息的哈希，对称加密，对称解密，签名和签名验证功能。
 *  目前版本支持如下功能：
 *  1. md5哈希
 *  2. sha哈希，256位，384位和512位
 *  3. des对称加密解密
 *  4. RSA的非对称加密，解密，签名，认证功能。（默认RSA秘钥为1024位）
 *                                                                            
 *  @author   Dong Han @ Alibaba
 *  @email    hd275562@alibaba-inc.com
 *  @version  1.0.0.1
 *  @date     2020.10.09
 *
 */

#pragma once
#ifndef DAMO_SDK_ONLINE_MANAGER_COPENSSL_HPP
#define DAMO_SDK_ONLINE_MANAGER_COPENSSL_HPP

#include <string>
#include <vector>
#include <cassert>
#include <cstring>
#include <iostream> 
#include <fstream>
#include <sstream> 
#include "base64.hpp"
#include "openssl/md5.h" 
#include "openssl/sha.h"
#include "openssl/des.h" 
#include "openssl/rsa.h"    
#include "openssl/pem.h" 
#include "openssl/evp.h"

// RSA加密参数 //    
#define KEY_LENGTH  1024             // 默认的RSA秘钥长度
#define PUB_KEY_FILE "pubkey.pem"    // 默认的公钥存储文件  
#define PRI_KEY_FILE "prikey.pem"    // 默认的私钥存储文件

class COpenSSL
{
public:
	COpenSSL();
	~COpenSSL();

     /** 
      * @brief md5哈希
      * @param srcStr 输入字符串
	 * @param encodedHexStr 哈希结果输出字符串
      *
      * @return 无
      */
	void md5(const std::string &srcStr, std::string &encodedHexStr);

     /** 
      * @brief SHA哈希（256位）
      * @param srcStr 输入字符串
	 * @param encodedHexStr 哈希结果输出字符串
      *
      * @return 无
      */
	void sha256(const std::string &srcStr, std::string &encodedHexStr);

	/** 
      * @brief SHA哈希（384位）
      * @param srcStr 输入字符串
	 * @param encodedHexStr 哈希结果输出字符串
      *
      * @return 无
      */
	void sha384(const std::string &srcStr, std::string &encodedHexStr);

	/** 
      * @brief SHA哈希（512位）
      * @param srcStr 输入字符串
	 * @param encodedHexStr 哈希结果输出字符串
      *
      * @return 无
      */ 
	void sha512(const std::string &srcStr, std::string &encodedHexStr);
   
	/** 
      * @brief DES对称加密，ECB加密
      * @param srcStr 输入明文
	 * @param key 加密秘钥
      *
      * @return 输出密文
      */  
	std::string des_encrypt(const std::string &clearText, const std::string &key);

	/** 
      * @brief DES对称解密，ECB解密
      * @param srcStr 输入密文
	 * @param key 解密秘钥
      *
      * @return 输出明文
      */       
	std::string des_decrypt(const std::string &cipherText, const std::string &key);

	/** 
      * @brief 生成RSA秘钥对函数
      * @param srcKey strKey[0]为公钥，strKey[1]为私钥
      * 
      * @return 无
	 * @note 
	 *     如下命令行可以生成对应的秘钥，此时prikey是PKCS1格式，pubkey是PKCS8格式
	 *     openssl genrsa -out prikey.pem 1024   
	 *     openssl rsa - in privkey.pem - pubout - out pubkey.pem  
      */  
	void generateRSAKey(std::string strKey[2]);

	/** 
      * @brief RSA公钥加密信息
      * @param clearText 输入明文
	 * @param pubKey 加密公钥
      *
      * @return 输出密文
      */   
	std::string rsa_pub_encrypt(const std::string &clearText, const std::string &pubKey);

	/** 
      * @brief RSA私钥解密信息
      * @param cipherText 输入密文
	 * @param priKey 解密私钥
      *
      * @return 输出明文
      */
	std::string rsa_pri_decrypt(const std::string &cipherText, const std::string &priKey);

	/** 
      * @brief RSA私钥签名信息
	 * @param privateKey 签名用私钥
      * @param plainText 签名明文
      *
      * @return 输出签名信息
      */
	std::string signMessage(std::string privateKey, std::string plainText);

	/** 
      * @brief RSA公钥验证信息
	 * @param publicKey 验证用公钥
      * @param plainText 签名明文
	 * @param signatureBase64 签名信息
      *
      * @return 输出签名验证结果
	 * @retval true表示签名验证成功，false表示签名验证失败
      */ 
	bool verifySignature(std::string &publicKey, std::string &plainText, std::string &signatureBase64);

	/** 
      * @brief 从文件中读取Key字符串
	 * @param filename 储存key的文件全路径
      *
      * @return 从文件中读取的key字符串
	 * @retval 从文件中读取的key字符串
      */
    std::string readKeyFile(const std::string& filename);

private:
	RSA* createPrivateRSA(std::string key);
	RSA* createPublicRSA(std::string key);
	bool RSASign(RSA* rsa, const unsigned char* Msg, size_t MsgLen, unsigned char** EncMsg, size_t* MsgLenEnc);
	bool RSAVerifySignature(RSA* rsa, unsigned char* MsgHash, size_t MsgHashLen, const char* Msg, size_t MsgLen, bool* Authentic);

	void printHex(const char *title, const unsigned char *s, int len);

public:
     // 测试用RSA秘钥对
	std::string privateKey;
	std::string publicKey;
};

#endif  // DAMO_SDK_ONLINE_MANAGER_COPENSSL_HPP
