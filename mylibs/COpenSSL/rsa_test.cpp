#include <iostream>    
#include <string>     
#include "COpenSSL.h"

int main() 
{
	// 原始明文，对于1024位RSA，不要加密超过127字符的明文，出于兼容性考虑，不要超过117字符。
	//std::string srcText = "{\"funcName\":\"raw2jpg\",\"callCount\":12345}";
	std::string srcText = "0000000D_00050654-FFFA3203-1F8BFBFF_76036301-00F0B5FF-00C30000";

	std::string encryptText;
	std::string encryptHexText;
	std::string decryptText;

	COpenSSL ssl;

	std::cout << "=== 明文信息 ===" << std::endl;
	std::cout << srcText << std::endl << std::endl;

	// rsa
	std::cout << "=== rsa加解密 ===" << std::endl;
	std::string key[2];

	key[0] = 

	// RSA key pairs for test. 
	std::string pri_prefix = "-----BEGIN RSA PRIVATE KEY-----\n";
	std::string pri_suffix = "-----END RSA PRIVATE KEY-----\n";
	key[1] = 
		"MIICXgIBAAKBgQDT3YXzRLSdzbNpNS8QfujfY33MpONEPVMYsDzDIhSVuWvYYy6c\n"\
		"nmzSZrWsWLa6vrdZur0Gsf4tKJsZwVeWgXIiD0fuD+s2jxgR731jbsYoeAZuNqoV\n"\
		"40YAvsHDPb/fDHlB8MzbxkRVJwLQo1DGrbF6b1J+Rv9wCDn47zBJYvrheQIDAQAB\n"\
		"AoGBAJtJ73iTj19q+mnO1aRdoQq7veVVpk7KNDIQWzkbrcLgma+NYwjhBhphth+R\n"\
		"Fr5iM7nNKefSZt9qt+R01mI2lxQRJ/qc2NNZ7QTaYmGSJRCIyTFYTE0j2qOcm8TA\n"\
		"Kk1LeiWAzbF7k5VAo86YmiLCC+ol9WbRC0jPsgcpI6T20WkRAkEA/n8e5TDEQ4ry\n"\
		"Ovruy1Z6jkMME4bU16/VpZFBD/6wfHs0dn68GHjo7Sm11T08yGDrI41S2lgN0Awe\n"\
		"EqQmitWdowJBANUd7j5CC4fmEPpe4JC6FXv4PS+0x6nZBbuscLhdc5mRHaRTcN6w\n"\
		"4NSmI5XmtjE2JYJjO83vXMn5gXCPYu61PjMCQQCLDybwkN8NEQUe2TJWBSDeTyBw\n"\
		"IwJ2AGw7Fc15Ue9ZdXDLNqDMtnR/8oSayeVGkD6rpHMbP3X8skJUaUFuJx8FAkAo\n"\
		"3oyJs/CyJxSqbvdxyb3FAF37gBeqIsxOqUsUkBdTI9kjYj0K97CmFxZL8OqPlWqs\n"\
		"Douxem247fg8tcKrNGaxAkEA3au6Q9fYqaXB+8kHv4GDiJjyRwQ8K6bStx51vNQv\n"\
		"Bv1aIvPBcJult6yzpE6ihMNRG08zckUR3z/qAPbllcLUwg==\n"\
		

	std::string pub_prefix = "-----BEGIN PUBLIC KEY-----\n";
	std::string pub_suffix = "-----END PUBLIC KEY-----\n";
	key[0] =  
		"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDT3YXzRLSdzbNpNS8QfujfY33M\n"\
		"pONEPVMYsDzDIhSVuWvYYy6cnmzSZrWsWLa6vrdZur0Gsf4tKJsZwVeWgXIiD0fu\n"\
		"D+s2jxgR731jbsYoeAZuNqoV40YAvsHDPb/fDHlB8MzbxkRVJwLQo1DGrbF6b1J+\n"\
		"Rv9wCDn47zBJYvrheQIDAQAB\n";
		
	//ssl.generateRSAKey(key);
	key[0] = pub_prefix + key[0] + pub_suffix;
	std::cout << "公钥：" << std::endl;
	std::cout << key[0] << std::endl;

	bool pub_ok = ssl.rsa_verify_pubkey(key[0]);
	if(!pub_ok)
	{
		std::cout << "Invalide Public Key. " << std::endl;
		return -1;
	}

	key[1] = pri_prefix + key[1] + pri_suffix;
	std::cout << "私钥：" << std::endl;
	std::cout << key[1] << std::endl;

	bool pri_ok = ssl.rsa_verify_prikey(key[1]);
	if(!pri_ok)
	{
		std::cout << "Invalide Private Key. " << std::endl;
		return -1;
	}

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