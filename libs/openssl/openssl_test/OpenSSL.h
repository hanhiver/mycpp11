#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <cassert>
#include <cstring>
#include <iostream> 
#include "base64.h"
#include "openssl/md5.h" 
#include "openssl/sha.h"
#include "openssl/des.h" 
#include "openssl/rsa.h"    
#include "openssl/pem.h" 
#include "openssl/evp.h"

// ---- rsa encrypt ---- //    
#define KEY_LENGTH  1024             // length of the key
#define PUB_KEY_FILE "pubkey.pem"    // path to the public key  
#define PRI_KEY_FILE "prikey.pem"    // path to the private key. 

class COpenSSL
{
public:
	COpenSSL();
	~COpenSSL();

	// ---- md5 hash ---- // 
	void md5(const std::string &srcStr, std::string &encodedHexStr);

	// ---- sha256 hash ---- //  
	void sha256(const std::string &srcStr, std::string &encodedHexStr);

	// ---- des symmetric encription ---- //    
	// encrypt ecb mode:  
	std::string des_encrypt(const std::string &clearText, const std::string &key);
	// decrypt ecb mode:     
	std::string des_decrypt(const std::string &cipherText, const std::string &key);

	// function to generate the key pair.   
	void generateRSAKey(std::string strKey[2]);

	// command line to create private key and public key. 
	// openssl genrsa -out prikey.pem 1024   
	// openssl rsa - in privkey.pem - pubout - out pubkey.pem  

	// public key encription
	std::string rsa_pub_encrypt(const std::string &clearText, const std::string &pubKey);
	// private key decription
	std::string rsa_pri_decrypt(const std::string &cipherText, const std::string &priKey);

	// private key signature
	std::string signMessage(std::string privateKey, std::string plainText);
	// publich key verification 
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

