#include <iostream>    
#include <string>     
#include "COpenSSL.h"

int main() 
{
	// 原始明文，对于1024位RSA，不要加密超过127字符的明文，出于兼容性考虑，不要超过117字符。
	std::string srcText = "{\"funcName\":\"raw2jpg\",\"callCount\":12345}";

	std::string encryptText;
	std::string encryptHexText;
	std::string decryptText;

	COpenSSL ssl;

	std::cout << "=== 明文信息 ===" << std::endl;
	std::cout << srcText << std::endl << std::endl;

	// md5    
	std::cout << "=== md5哈希 ===" << std::endl;
	ssl.md5(srcText, encryptHexText);
	std::cout << "摘要串:" << encryptHexText << std::endl << std::endl;

	// sha256    
	std::cout << "=== sha256哈希 ===" << std::endl;
	ssl.sha256(srcText, encryptHexText);
	std::cout << "摘要:" << encryptHexText << std::endl << std::endl;

	// des    
	std::cout << "=== des加解密 ===" << std::endl;
	std::string desKey = "12345";
	encryptText = ssl.des_encrypt(srcText, desKey);
	std::cout << "加密字符：" << std::endl;
	std::cout << encryptText << std::endl;
	decryptText = ssl.des_decrypt(encryptText, desKey);
	std::cout << "解密字符：" << std::endl;
	std::cout << decryptText << std::endl << std::endl;

	// rsa
	std::cout << "=== rsa加解密 ===" << std::endl;
	std::string key[2];
	ssl.generateRSAKey(key);
	std::cout << "公钥：" << std::endl;
	std::cout << key[0] << std::endl;
	std::cout << "私钥：" << std::endl;
	std::cout << key[1] << std::endl;
	encryptText = ssl.rsa_pub_encrypt(srcText, key[0]);
	std::cout << "加密字符：" << std::endl;
	std::cout << encryptText << std::endl;
	std::string transferText = base64_encode((const unsigned char *)encryptText.c_str(), encryptText.length());
	std::cout << "base64传输密文：\n" << transferText << std::endl;
	encryptText = base64_decode(transferText);
	decryptText = ssl.rsa_pri_decrypt(encryptText, key[1]);
	std::cout << "解密字符：" << std::endl;
	std::cout << decryptText << std::endl << std::endl;

	//rsa+md5签名验证
	std::string signature = ssl.signMessage(ssl.privateKey, srcText);
	std::cout << "签名base64字符：" << std::endl;
	std::cout << signature << std::endl << std::endl;
	bool authentic = ssl.verifySignature(ssl.publicKey, srcText, signature);
	if (authentic) 
	{
		std::cout << "签名验证成功！" << std::endl << std::endl;
	}
	else 
	{
		std::cout << "签名验证失败！" << std::endl << std::endl;
	}
	
	return 0;
}