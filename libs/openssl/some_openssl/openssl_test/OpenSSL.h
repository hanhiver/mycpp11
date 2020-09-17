#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <cassert>
#include "base64.h"
#include "openssl/md5.h" 
#include "openssl/sha.h"
#include "openssl/des.h" 
#include "openssl/rsa.h"    
#include "openssl/pem.h" 

// ---- rsa非对称加解密 ---- //    
#define KEY_LENGTH  1024              // 密钥长度  
#define PUB_KEY_FILE "pubkey.pem"    // 公钥路径  
#define PRI_KEY_FILE "prikey.pem"    // 私钥路径 

class COpenSSL
{
public:
	COpenSSL();
	~COpenSSL();

	// ---- md5摘要哈希 ---- // 
	void md5(const std::string &srcStr, std::string &encodedHexStr);

	// ---- sha256摘要哈希 ---- //  
	void sha256(const std::string &srcStr, std::string &encodedHexStr);

	// ---- des对称加解密 ---- //    
	// 加密 ecb模式    
	std::string des_encrypt(const std::string &clearText, const std::string &key);
	// 解密 ecb模式    
	std::string des_decrypt(const std::string &cipherText, const std::string &key);

	// 函数方法生成密钥对   
	void generateRSAKey(std::string strKey[2]);

	// 命令行方法生成公私钥对（begin public key/ begin private key）  
	// 找到openssl命令行工具，运行以下  
	// openssl genrsa -out prikey.pem 1024   
	// openssl rsa - in privkey.pem - pubout - out pubkey.pem  

	// 公钥加密    
	std::string rsa_pub_encrypt(const std::string &clearText, const std::string &pubKey);
	// 私钥解密    
	std::string rsa_pri_decrypt(const std::string &cipherText, const std::string &priKey);

	//私钥签名
	std::string signMessage(std::string privateKey, std::string plainText);
	//公钥验证
	bool verifySignature(std::string &publicKey, std::string &plainText, std::string &signatureBase64);

private:
	RSA* createPrivateRSA(std::string key);
	RSA* createPublicRSA(std::string key);
	bool RSASign(RSA* rsa, const unsigned char* Msg, size_t MsgLen, unsigned char** EncMsg, size_t* MsgLenEnc);
	bool RSAVerifySignature(RSA* rsa, unsigned char* MsgHash, size_t MsgHashLen, const char* Msg, size_t MsgLen, bool* Authentic);

	void printHex(const char *title, const unsigned char *s, int len);

public:
	std::string privateKey;
	std::string publicKey;
};

