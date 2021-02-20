/*
g++ -c OpenSSL.cpp
g++ -c base64.cpp
g++ -c tohex.cpp
g++ -c main.cpp
g++ -o main.out main.o base64.o OpenSSL.o tohex.o -lcrypto -lpthread
*/

#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>     
#include "openssl/md5.h" 
#include "openssl/sha.h"
#include "openssl/des.h" 
#include "openssl/rsa.h"    
#include "openssl/pem.h" 
#include "openssl/evp.h"

std::string readKeyFile(std::string filename)
{
	std::string keyFromFile;
	std::ifstream inputFile;
	inputFile.open(filename, std::ios_base::out);
	std::ostringstream buf;
	char ch;
	while(buf && inputFile.get(ch))
	{
		buf.put(ch);
	}
	inputFile.close();
	return buf.str();
}

bool RSAVerifySignature(RSA* rsa, unsigned char* MsgHash, size_t MsgHashLen, const char* Msg, size_t MsgLen, bool* Authentic)
{
	*Authentic = false;
	EVP_PKEY* pubKey = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(pubKey, rsa);
	EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

	if (EVP_DigestVerifyInit(m_RSAVerifyCtx, NULL, EVP_md5(), NULL, pubKey) <= 0) {
		return false;
	}
	if (EVP_DigestVerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) <= 0) {
		return false;
	}
	int AuthStatus = EVP_DigestVerifyFinal(m_RSAVerifyCtx, MsgHash, MsgHashLen);
	if (AuthStatus == 1) {
		*Authentic = true;
		EVP_MD_CTX_reset(m_RSAVerifyCtx);
		return true;
	}
	else if (AuthStatus == 0) {
		*Authentic = false;
		EVP_MD_CTX_reset(m_RSAVerifyCtx);
		return true;
	}
	else {
		*Authentic = false;
		EVP_MD_CTX_reset(m_RSAVerifyCtx);
		return false;
	}
}

int main() 
{

	bool authentic;
	RSA *publicRSA = NULL;
	BIO *keybio;

	std::string document = "{\"zone-id\":\"cn-zhangjiakou-c\",\"serial-number\":\"4453b924-c169-45a7-9478-0dcdd94628b3\",\"instance-id\":\"i-8vb9b97xf7msxi4k6tgx\",\"region-id\":\"cn-zhangjiakou\",\"private-ipv4\":\"11.160.137.194\",\"owner-account-id\":\"1900050632443592\",\"mac\":\"00:16:3e:0b:5c:f8\",\"image-id\":\"m-8vbipaljoi4ep0rcxght\",\"instance-type\":\"ecs.gn6v-c8g1.8xlarge\",\"audience\":\"abc\"}";
	std::string signature = "MIIDLwYJKoZIhvcNAQcCoIIDIDCCAxwCAQExCzAJBgUrDgMCGgUAMIIBaQYJKoZIhvcNAQcBoIIBWgSCAVZ7InpvbmUtaWQiOiJjbi16aGFuZ2ppYWtvdS1jIiwic2VyaWFsLW51bWJlciI6IjQ0NTNiOTI0LWMxNjktNDVhNy05NDc4LTBkY2RkOTQ2MjhiMyIsImluc3RhbmNlLWlkIjoiaS04dmI5Yjk3eGY3bXN4aTRrNnRneCIsInJlZ2lvbi1pZCI6ImNuLXpoYW5namlha291IiwicHJpdmF0ZS1pcHY0IjoiMTEuMTYwLjEzNy4xOTQiLCJvd25lci1hY2NvdW50LWlkIjoiMTkwMDA1MDYzMjQ0MzU5MiIsIm1hYyI6IjAwOjE2OjNlOjBiOjVjOmY4IiwiaW1hZ2UtaWQiOiJtLTh2YmlwYWxqb2k0ZXAwcmN4Z2h0IiwiaW5zdGFuY2UtdHlwZSI6ImVjcy5nbjZ2LWM4ZzEuOHhsYXJnZSIsImF1ZGllbmNlIjoiYWJjIn0xggGbMIIBlwIBATB0MGwxEDAOBgNVBAYTB1Vua25vd24xEDAOBgNVBAgTB1Vua25vd24xEDAOBgNVBAcTB1Vua25vd24xEDAOBgNVBAoTB1Vua25vd24xEDAOBgNVBAsTB1Vua25vd24xEDAOBgNVBAMTB1Vua25vd24CBGZm0YcwCQYFKw4DAhoFADANBgkqhkiG9w0BAQEFAASCAQBC6YahjbbGPJHMN71fuSD9swtAYd+FpCEWf906WFbRgScdxJTB07IQxuaEUHhUTso2Q2FQOhMrHnLFr5e9MceutOKWv7L3RNxOnmbBGILu1i/B4Dth7DbaVaPsF8YC/ksEX7RtKiPS+J9haPfAREbtlVvOv4GZ9NV7TD9cizTTFTwowmCKSO6nYlBiqDZoSqq5J2aJE0ffiJysIngDIGYQRLRe15fAbMGiJishuwiO0dzt/4Z+ac9rqr467mo6vTZLdeXyKXEqj8kM05gnE7S8nmfPXLrur5hcMslCcQoRJv+zoxwwzVk13o6Aoj7I2w2b+JwkwNsnFmP3+WCO+ZA5";
	std::string ali_key = readKeyFile("/home/hd275562/myprog/mycpp11/libs/openssl/openssl_cmake318/aliyun.pub");

	keybio = BIO_new_mem_buf((void*)ali_key.c_str(), -1);
	publicRSA = PEM_read_bio_RSA_PUBKEY(keybio, &publicRSA, NULL, NULL);

	bool result = RSAVerifySignature(publicRSA, (unsigned char*)signature.c_str(), signature.size(), document.c_str(), document.length(), &authentic);
	if (result & authentic) {
		std::cout << "验证成功！" << std::endl << std::endl;
	}
	else {
		std::cout << "验证失败！" << std::endl << std::endl;
	}

	return 0;
}