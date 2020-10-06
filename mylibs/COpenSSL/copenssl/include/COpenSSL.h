#pragma once
#ifndef DAMO_COPENSSL_H
#define DAMO_COPENSSL_H

#include <string>
#include <vector>
#include <cassert>
#include <cstring>
#include <iostream> 
#include <fstream>
#include <sstream> 
#include "base64.h"
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

	// ---- md5哈希 ---- // 
	void md5(const std::string &srcStr, std::string &encodedHexStr);

	// ---- sha256哈希 ---- //  
	void sha256(const std::string &srcStr, std::string &encodedHexStr);

	// ---- sha384哈希 ---- //  
	void sha384(const std::string &srcStr, std::string &encodedHexStr);

	// ---- sha512哈希 ---- //  
	void sha512(const std::string &srcStr, std::string &encodedHexStr);

	// ---- des对称加密 ---- //    
	// ecb加密:  
	std::string des_encrypt(const std::string &clearText, const std::string &key);
	// ecb解密:     
	std::string des_decrypt(const std::string &cipherText, const std::string &key);

	// 生成RSA秘钥对函数，strKey[0]为公钥，strKey[1]为私钥
	void generateRSAKey(std::string strKey[2]);

	// 如下命令行可以生成对应的秘钥，此时prikey是PKCS1格式，pubkey是PKCS8格式
	// openssl genrsa -out prikey.pem 1024   
	// openssl rsa - in privkey.pem - pubout - out pubkey.pem  

	// RSA公钥加密信息
	std::string rsa_pub_encrypt(const std::string &clearText, const std::string &pubKey);
	// RSA私钥解密信息
	std::string rsa_pri_decrypt(const std::string &cipherText, const std::string &priKey);

	// RSA私钥签名信息
	std::string signMessage(std::string privateKey, std::string plainText);
	// RSA公钥验证信息 
	bool verifySignature(std::string &publicKey, std::string &plainText, std::string &signatureBase64);

    // 从文件中读取Key字符串
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

#endif  // DAMO_COPENSSL_H
