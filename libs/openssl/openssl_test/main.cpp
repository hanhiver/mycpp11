#include <iostream>    
#include <string>     
#include "OpenSSL.h"

int main() 
{
	// 原始明文    
	std::string srcText = "123";

	std::string encryptText;
	std::string encryptHexText;
	std::string decryptText;

	COpenSSL ssl;

	std::cout << "=== 原始明文 ===" << std::endl;
	std::cout << srcText << std::endl << std::endl;

	// md5    
	std::cout << "=== md5哈希 ===" << std::endl;
	ssl.md5(srcText, encryptHexText);
	std::cout << "摘要串:" << encryptHexText << std::endl << std::endl;

	// sha256    
	std::cout << "=== sha256哈希 ===" << std::endl;
	ssl.sha256(srcText, encryptHexText);
	std::cout << "摘要串:" << encryptHexText << std::endl << std::endl;

	// des    
	std::cout << "=== des加解密 ===" << std::endl;
	std::string desKey = "12345";
	encryptText = ssl.des_encrypt(srcText, desKey);
	std::cout << "加密字符： " << std::endl;
	std::cout << encryptText << std::endl;
	decryptText = ssl.des_decrypt(encryptText, desKey);
	std::cout << "解密字符： " << std::endl;
	std::cout << decryptText << std::endl << std::endl;

	// rsa加解密    
	std::cout << "=== rsa加解密 ===" << std::endl;
	std::string key[2];
	ssl.generateRSAKey(key);
	std::cout << "公钥: " << std::endl;
	std::cout << key[0] << std::endl;
	std::cout << "私钥： " << std::endl;
	std::cout << key[1] << std::endl;
	encryptText = ssl.rsa_pub_encrypt(srcText, key[0]);
	std::cout << "加密字符： " << std::endl;
	std::cout << encryptText << std::endl;
	decryptText = ssl.rsa_pri_decrypt(encryptText, key[1]);
	std::cout << "解密字符： " << std::endl;
	std::cout << decryptText << std::endl << std::endl;

	//rsa+md5签名验证
	std::string signature = ssl.signMessage(ssl.privateKey, srcText);
	std::cout << "签名base64字符： " << std::endl;
	std::cout << signature << std::endl << std::endl;
	bool authentic = ssl.verifySignature(ssl.publicKey, srcText, signature);
	if (authentic) {
		std::cout << "Authentic" << std::endl << std::endl;
	}
	else {
		std::cout << "Not Authentic" << std::endl << std::endl;
	}

	return 0;
}