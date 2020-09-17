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

// ---- rsa�ǶԳƼӽ��� ---- //    
#define KEY_LENGTH  1024              // ��Կ����  
#define PUB_KEY_FILE "pubkey.pem"    // ��Կ·��  
#define PRI_KEY_FILE "prikey.pem"    // ˽Կ·�� 

class COpenSSL
{
public:
	COpenSSL();
	~COpenSSL();

	// ---- md5ժҪ��ϣ ---- // 
	void md5(const std::string &srcStr, std::string &encodedHexStr);

	// ---- sha256ժҪ��ϣ ---- //  
	void sha256(const std::string &srcStr, std::string &encodedHexStr);

	// ---- des�ԳƼӽ��� ---- //    
	// ���� ecbģʽ    
	std::string des_encrypt(const std::string &clearText, const std::string &key);
	// ���� ecbģʽ    
	std::string des_decrypt(const std::string &cipherText, const std::string &key);

	// ��������������Կ��   
	void generateRSAKey(std::string strKey[2]);

	// �����з������ɹ�˽Կ�ԣ�begin public key/ begin private key��  
	// �ҵ�openssl�����й��ߣ���������  
	// openssl genrsa -out prikey.pem 1024   
	// openssl rsa - in privkey.pem - pubout - out pubkey.pem  

	// ��Կ����    
	std::string rsa_pub_encrypt(const std::string &clearText, const std::string &pubKey);
	// ˽Կ����    
	std::string rsa_pri_decrypt(const std::string &cipherText, const std::string &priKey);

	//˽Կǩ��
	std::string signMessage(std::string privateKey, std::string plainText);
	//��Կ��֤
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

