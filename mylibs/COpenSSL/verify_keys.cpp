#include <iostream>    
#include <string>     
#include "COpenSSL.h"

int main() 
{
	// 原始明文，对于1024位RSA，不要加密超过127字符的明文，出于兼容性考虑，不要超过117字符。
	//std::string srcText = "{\"funcName\":\"raw2jpg\",\"callCount\":12345}";
	std::string srcText = "{\"curTime\":1602729662863,\"funcNameList\":[],\"keyInfo\":{\"keyIndex\":\"1116dcd3fe3f42779ddbbad77cc47c9a\",\"keyType\":\"RSA\"},\"sdkName\":\"RAW2JPG\",\"vendorName\":\"Miaoxiu\",\"version\":1}";
	std::string key = "-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDT3YXzRLSdzbNpNS8QfujfY33M\npONEPVMYsDzDIhSVuWvYYy6cnmzSZrWsWLa6vrdZur0Gsf4tKJsZwVeWgXIiD0fu\nD+s2jxgR731jbsYoeAZuNqoV40YAvsHDPb/fDHlB8MzbxkRVJwLQo1DGrbF6b1J+\nRv9wCDn47zBJYvrheQIDAQAB\n-----END PUBLIC KEY-----";
	std::string signature = "nY8z99y6FyXE37szSlByOGohwZI6vZKLF69TZz0M6I7NeSMp7M0yVYDSh1gw0+FsD+0TdD09ms4cUhU8D5AavZDFks8W9nWIl04llMnLisx020L4goaczEUbl5wWwgCBK63YdTn/UnwxWgB0Qxc533pCy+k/mV27FCgMS+xpeiY=";
	std::string encryptText;
	std::string encryptHexText;
	std::string decryptText;

	COpenSSL ssl;

	std::cout << "=== 明文信息 ===" << std::endl;
	std::cout << ssl.publicKey;
	std::cout << srcText << std::endl << std::endl;
	std::cout << "签名： \n" << signature << std::endl; 
	/*
	std::string pub_key = ssl.publicKey;
	pub_key[28] = 'X';
	std::cout << "公钥正确验证：" << std::boolalpha << ssl.rsa_verify_pubkey(pub_key) << std::endl;

	std::string pri_key = ssl.privateKey;
	pri_key[28] = 'X';
	std::cout << "公钥正确验证：" << std::boolalpha << ssl.rsa_verify_prikey(pri_key) << std::endl;

	*/

	/*
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
	*/
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