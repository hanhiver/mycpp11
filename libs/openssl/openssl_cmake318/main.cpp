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
#include "OpenSSL.h"
#include "tohex.h"

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

int main() 
{

	// 原始明文
	//std::string srcText = "{\"longFuncName\":\"shumiaozusuanfa\",\"callCountAgain\":1212121}";
	std::string srcText = "0000000D_00050654-FFFA3203-1F8BFBFF_76036301-00F0B5FF-00C30000i-8vb9b97xf7msxi4k6tgx";

	std::string encryptText;
	std::string encryptHexText;
	std::string decryptText;

	COpenSSL ssl;

	std::cout << "=== 明文信息 ===" << std::endl;
	std::cout << srcText << ", length: " << srcText.size() << std::endl << std::endl;

	// md5    
	std::cout << "=== md5哈希 ===" << std::endl;
	ssl.md5(srcText, encryptHexText);
	std::cout << "摘要串:" << encryptHexText << std::endl << std::endl;

	// rsa
	std::cout << "=== rsa加解密 ===" << std::endl;
	std::string key[2];
	//ssl.generateRSAKey(key);
	
	key[0] = readKeyFile("/home/hd275562/myprog/mycpp11/libs/openssl/genkey/ppub.pem");
	key[1] = readKeyFile("/home/hd275562/myprog/mycpp11/libs/openssl/genkey/pri.pem");

	std::cout << "公钥：" << std::endl;
	std::cout << key[0] << std::endl;
	std::cout << "私钥：" << std::endl;
	std::cout << key[1] << std::endl;
	encryptText = ssl.rsa_pub_encrypt(srcText, key[0]);
	std::cout << "加密字符：" << std::endl;
	std::cout << encryptText << std::endl;
	// 加密后的字符经过base64加码后传输
	std::string encryptBase64 = base64_encode((const unsigned char*)encryptText.c_str(), encryptText.length());
	
	// 加密后字符串写入文件
	std::ofstream outfile;
    outfile.open("msg.txt", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);  //删除文件重写
    outfile << encryptBase64; 
    outfile.close();

	// 从文件中重新读出字符串
	std::ifstream infile; 
	infile.open("msg.txt", std::ios_base::in | std::ios_base::binary);	
	std::ostringstream buf;
	char ch;
	while(buf && infile.get(ch))
	{
		buf.put(ch);
	}
	//返回与流对象buf关联的字符串
	std::string filein = buf.str();
	infile.close();

	std::cout << "base64传输密文：\n" << filein << std::endl;
	encryptText = base64_decode(filein); 
	//std::cout << "HEX: \n" << strToHex(encryptText, "") << std::endl;
	//std::cout << "base64: \n" << base64_encode((const unsigned char*)encryptText.c_str(), encryptText.length()) << std::endl;
	
	decryptText = ssl.rsa_pri_decrypt(encryptText, key[1]);
	std::cout << "解密字符：" << std::endl;
	std::cout << decryptText << ", length: " << decryptText.size() << std::endl << std::endl;

	//rsa+md5签名验证
	std::string signature = ssl.signMessage(key[1], srcText);
	//std::string signature = "cWedxjfVOmveUUOVj8S04x6rRIRSUgNnt6qHH0bL0SoOtd0oCR7OcReIfu+qa63fWiWXXfwy865nZ7KGSTjXTYOtBOdmSk0JpmLu9q0dan22W9P1eVCHanHqfxhHLfcK5L4Mhte+TSX1DRskb9mSb2HKBcZykQFjrBSIMOIZtsM=";
	//std::cout << "签名base64-decode: " << base64_encode((unsigned char*)srcText.c_str(), srcText.length());
	std::cout << "签名base64字符：" << std::endl;
	std::cout << signature << std::endl;
	std::cout << "验证签名字符串：";
	bool authentic = ssl.verifySignature(key[0], srcText, signature);
	if (authentic) {
		std::cout << "验证成功！" << std::endl << std::endl;
	}
	else {
		std::cout << "验证失败！" << std::endl << std::endl;
	}

	return 0;
}