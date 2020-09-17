#include "OpenSSL.h"

COpenSSL::COpenSSL()
{
	privateKey = "-----BEGIN RSA PRIVATE KEY-----\n"\
		"MIICXgIBAAKBgQCd9MBL+TqW6RQztVC1611LKCtt7KDGqiudAFEpujTrOWxfEIs/\n"\
		"wiC0noj6neKskdlIIfmLkiE0h0amTqziDnIo21RMTIQwQ6gX7YZLUg1Ck4kczVjO\n"\
		"vynqAYKWQyGISRr36XIzRuB7WY3YX+ciVp4zR72yizrx+OduDioesslcawIDAQAB\n"\
		"AoGBAIgKT8QfNvLac2fFdWn4+DTOt/jIn//6d+2UZFLH6OPeZRPLL+MN0xU8pUUT\n"\
		"zjJKuxSBDmfCx45yI8sAX62iO3bNKPF1cyvoi9JNbtjez0xxdiHPzrzFlCh339fJ\n"\
		"Zyny6+dj2umv78evHJYthGdCy5V/QwiuVxD0y/Qv10RA/u6hAkEAqPBRgKWsqbAg\n"\
		"G0mI8MhNS+NR1vAH0XXCmdUba1lBZXeesq9UsH4webSZzj0K8Rtma4u2utB8zLhT\n"\
		"Uu2mP9hCPwJBAO9bg4CvuFKwv46+jdDAG8qoFP2glC8sbN69ynrmk6f6rElh6Yzj\n"\
		"nAct0OROndTaVV1mNuC5/rBJ/Hi/rA+6QtUCQQCnImIvuTiSBDovZNfDBxdZvcJo\n"\
		"t720XyGwWWIwGPSW8vohY06Q8bb5oVAM9t1NXcM9INMeDUd6rd1ZjN3OCiC3AkBA\n"\
		"lD5MsBxZIxrr1nnIwqw851CShYq1l5TgG/DPa/qWrcliGyq6OobUYQYlMxjeXvH9\n"\
		"OyC/TS9sPOoDYiN4MtbpAkEApZ4sZ/oJ/+OV9ojdXLbkYb03uK3h4k5Musw1uPGR\n"\
		"KAO/c/GNYwHbuKVFNm6GBM2BqFcLX22y14XfH0D1fznWbA==\n"\
		"-----END RSA PRIVATE KEY-----\n\0";

	publicKey = "-----BEGIN PUBLIC KEY-----\n"\
		"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCd9MBL+TqW6RQztVC1611LKCtt\n"\
		"7KDGqiudAFEpujTrOWxfEIs/wiC0noj6neKskdlIIfmLkiE0h0amTqziDnIo21RM\n"\
		"TIQwQ6gX7YZLUg1Ck4kczVjOvynqAYKWQyGISRr36XIzRuB7WY3YX+ciVp4zR72y\n"\
		"izrx+OduDioesslcawIDAQAB\n"\
		"-----END PUBLIC KEY-----\n";
}


COpenSSL::~COpenSSL()
{
}
   
void COpenSSL::md5(const std::string &srcStr, std::string &encodedHexStr)
{
	// 调用md5哈希    
	unsigned char mdStr[33] = { 0 };
	MD5((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);

	// 哈希后的十六进制串 32字节    
	char buf[65] = { 0 };
	char tmp[3] = { 0 };
	for (int i = 0; i < 32; i++)
	{
		sprintf(tmp, "%02x", mdStr[i]);
		strcat(buf, tmp);
	}
	buf[32] = '\0'; // 后面都是0，从32字节截断    
	encodedHexStr = std::string(buf);
}
  
void COpenSSL::sha256(const std::string &srcStr, std::string &encodedHexStr)
{
	// 调用sha256哈希    
	unsigned char mdStr[65] = { 0 };
	SHA256((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);

	// 哈希后的十六进制串 32字节    
	char buf[129] = { 0 };
	char tmp[3] = { 0 };
	for (int i = 0; i < 32; i++)
	{
		sprintf(tmp, "%02x", mdStr[i]);
		strcat(buf, tmp);
	}
	buf[128] = '\0'; // 后面都是0，从32字节截断    
	encodedHexStr = std::string(buf);
}

std::string COpenSSL::des_encrypt(const std::string &clearText, const std::string &key)
{
	std::string cipherText; // 密文    

	DES_cblock keyEncrypt;
	memset(keyEncrypt, 0, 8);

	// 构造补齐后的密钥    
	if (key.length() <= 8)
		memcpy(keyEncrypt, key.c_str(), key.length());
	else
		memcpy(keyEncrypt, key.c_str(), 8);

	// 密钥置换    
	DES_key_schedule keySchedule;
	DES_set_key_unchecked(&keyEncrypt, &keySchedule);

	// 循环加密，每8字节一次    
	const_DES_cblock inputText;
	DES_cblock outputText;
	std::vector<unsigned char> vecCiphertext;
	unsigned char tmp[8];

	for (int i = 0; i < clearText.length() / 8; i++)
	{
		memcpy(inputText, clearText.c_str() + i * 8, 8);
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
		memcpy(tmp, outputText, 8);

		for (int j = 0; j < 8; j++)
			vecCiphertext.push_back(tmp[j]);
	}

	if (clearText.length() % 8 != 0)
	{
		int tmp1 = clearText.length() / 8 * 8;
		int tmp2 = clearText.length() - tmp1;
		memset(inputText, 0, 8);
		memcpy(inputText, clearText.c_str() + tmp1, tmp2);
		// 加密函数    
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
		memcpy(tmp, outputText, 8);

		for (int j = 0; j < 8; j++)
			vecCiphertext.push_back(tmp[j]);
	}

	cipherText.clear();
	cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());

	return cipherText;
}

std::string COpenSSL::des_decrypt(const std::string &cipherText, const std::string &key)
{
	std::string clearText; // 明文    

	DES_cblock keyEncrypt;
	memset(keyEncrypt, 0, 8);

	if (key.length() <= 8)
		memcpy(keyEncrypt, key.c_str(), key.length());
	else
		memcpy(keyEncrypt, key.c_str(), 8);

	DES_key_schedule keySchedule;
	DES_set_key_unchecked(&keyEncrypt, &keySchedule);

	const_DES_cblock inputText;
	DES_cblock outputText;
	std::vector<unsigned char> vecCleartext;
	unsigned char tmp[8];

	for (int i = 0; i < cipherText.length() / 8; i++)
	{
		memcpy(inputText, cipherText.c_str() + i * 8, 8);
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
		memcpy(tmp, outputText, 8);

		for (int j = 0; j < 8; j++)
			vecCleartext.push_back(tmp[j]);
	}

	if (cipherText.length() % 8 != 0)
	{
		int tmp1 = cipherText.length() / 8 * 8;
		int tmp2 = cipherText.length() - tmp1;
		memset(inputText, 0, 8);
		memcpy(inputText, cipherText.c_str() + tmp1, tmp2);
		// 解密函数    
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
		memcpy(tmp, outputText, 8);

		for (int j = 0; j < 8; j++)
			vecCleartext.push_back(tmp[j]);
	}

	clearText.clear();
	clearText.assign(vecCleartext.begin(), vecCleartext.end());

	return clearText;
}

void COpenSSL::generateRSAKey(std::string strKey[2])
{
	// 公私密钥对    
	size_t pri_len;
	size_t pub_len;
	char *pri_key = NULL;
	char *pub_key = NULL;

	// 生成密钥对    
	RSA *keypair = RSA_generate_key(KEY_LENGTH, RSA_3, NULL, NULL);

	BIO *pri = BIO_new(BIO_s_mem());
	BIO *pub = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
	PEM_write_bio_RSAPublicKey(pub, keypair);

	// 获取长度    
	pri_len = BIO_pending(pri);
	pub_len = BIO_pending(pub);

	// 密钥对读取到字符串    
	pri_key = (char *)malloc(pri_len + 1);
	pub_key = (char *)malloc(pub_len + 1);

	BIO_read(pri, pri_key, pri_len);
	BIO_read(pub, pub_key, pub_len);

	pri_key[pri_len] = '\0';
	pub_key[pub_len] = '\0';

	// 存储密钥对    
	strKey[0] = pub_key;
	strKey[1] = pri_key;

	// 存储到磁盘（这种方式存储的是begin rsa public key/ begin rsa private key开头的）  
	FILE *pubFile = fopen(PUB_KEY_FILE, "w");
	if (pubFile == NULL)
	{
		assert(false);
		return;
	}
	fputs(pub_key, pubFile);
	fclose(pubFile);

	FILE *priFile = fopen(PRI_KEY_FILE, "w");
	if (priFile == NULL)
	{
		assert(false);
		return;
	}
	fputs(pri_key, priFile);
	fclose(priFile);

	// 内存释放  
	RSA_free(keypair);
	BIO_free_all(pub);
	BIO_free_all(pri);

	free(pri_key);
	free(pub_key);
}

std::string COpenSSL::rsa_pub_encrypt(const std::string &clearText, const std::string &pubKey)
{
	std::string strRet;
	RSA *rsa = NULL;
	BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);
	// 此处有三种方法  
	// 1, 读取内存里生成的密钥对，再从内存生成rsa  
	// 2, 读取磁盘里生成的密钥对文本文件，在从内存生成rsa  
	// 3，直接从读取文件指针生成rsa  
	RSA* pRSAPublicKey = RSA_new();
	rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);

	int len = RSA_size(rsa);
	char *encryptedText = (char *)malloc(len + 1);
	memset(encryptedText, 0, len + 1);

	// 加密函数  
	int ret = RSA_public_encrypt(clearText.length(), (const unsigned char*)clearText.c_str(), (unsigned char*)encryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = std::string(encryptedText, ret);

	// 释放内存  
	free(encryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}

std::string COpenSSL::rsa_pri_decrypt(const std::string &cipherText, const std::string &priKey)
{
	std::string strRet;
	RSA *rsa = RSA_new();
	BIO *keybio;
	keybio = BIO_new_mem_buf((unsigned char *)priKey.c_str(), -1);

	// 此处有三种方法  
	// 1, 读取内存里生成的密钥对，再从内存生成rsa  
	// 2, 读取磁盘里生成的密钥对文本文件，在从内存生成rsa  
	// 3，直接从读取文件指针生成rsa  
	rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

	int len = RSA_size(rsa);
	char *decryptedText = (char *)malloc(len + 1);
	memset(decryptedText, 0, len + 1);

	// 解密函数  
	int ret = RSA_private_decrypt(cipherText.length(), (const unsigned char*)cipherText.c_str(), (unsigned char*)decryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = std::string(decryptedText, ret);

	// 释放内存  
	free(decryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}

std::string COpenSSL::signMessage(std::string privateKey, std::string plainText)
{
	RSA* privateRSA = createPrivateRSA(privateKey);
	unsigned char* encMessage;
	size_t encMessageLength;

	RSASign(privateRSA, (unsigned char*)plainText.c_str(), plainText.size(), &encMessage, &encMessageLength);
	std::string signbase64 = base64_encode(encMessage, encMessageLength);
	free(encMessage);
	RSA_free(privateRSA);
	return signbase64;
}

bool COpenSSL::verifySignature(std::string &publicKey, std::string &plainText, std::string &signatureBase64)
{
	RSA* publicRSA = createPublicRSA(publicKey);
	unsigned char* encMessage;
	bool authentic;
	std::string encMessageTmp = base64_decode((char *)signatureBase64.c_str());
	bool result = RSAVerifySignature(publicRSA, (unsigned char*)encMessageTmp.c_str(), encMessageTmp.size(), plainText.c_str(), plainText.length(), &authentic);
	return result & authentic;
}

RSA* COpenSSL::createPrivateRSA(std::string key)
{
	RSA *rsa = NULL;
	const char* c_string = key.c_str();
	BIO * keybio = BIO_new_mem_buf((void*)c_string, -1);
	if (keybio == NULL) {
		return 0;
	}
	rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
	return rsa;
}

RSA* COpenSSL::createPublicRSA(std::string key)
{
	RSA *rsa = NULL;
	BIO *keybio;
	const char* c_string = key.c_str();
	keybio = BIO_new_mem_buf((void*)c_string, -1);
	if (keybio == NULL) {
		return 0;
	}
	rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
	return rsa;
}

bool COpenSSL::RSASign(RSA* rsa, const unsigned char* Msg, size_t MsgLen, unsigned char** EncMsg, size_t* MsgLenEnc)
{
	EVP_MD_CTX* m_RSASignCtx = EVP_MD_CTX_create();
	EVP_PKEY* priKey = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(priKey, rsa);
	if (EVP_DigestSignInit(m_RSASignCtx, NULL, EVP_md5(), NULL, priKey) <= 0) {
		return false;
	}
	if (EVP_DigestSignUpdate(m_RSASignCtx, Msg, MsgLen) <= 0) {
		return false;
	}
	if (EVP_DigestSignFinal(m_RSASignCtx, NULL, MsgLenEnc) <= 0) {
		return false;
	}
	*EncMsg = (unsigned char*)malloc(*MsgLenEnc);
	if (EVP_DigestSignFinal(m_RSASignCtx, *EncMsg, MsgLenEnc) <= 0) {
		return false;
	}
	EVP_MD_CTX_cleanup(m_RSASignCtx);
	return true;
}

bool COpenSSL::RSAVerifySignature(RSA* rsa, unsigned char* MsgHash, size_t MsgHashLen, const char* Msg, size_t MsgLen, bool* Authentic)
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
		EVP_MD_CTX_cleanup(m_RSAVerifyCtx);
		return true;
	}
	else if (AuthStatus == 0) {
		*Authentic = false;
		EVP_MD_CTX_cleanup(m_RSAVerifyCtx);
		return true;
	}
	else {
		*Authentic = false;
		EVP_MD_CTX_cleanup(m_RSAVerifyCtx);
		return false;
	}
}

void COpenSSL::printHex(const char *title, const unsigned char *s, int len)
{
	int n;
	printf("%s:", title);
	for (n = 0; n < len; ++n) {
		if ((n % 16) == 0) {
			printf("\n%04x", n);
		}
		printf(" %02x", s[n]);
	}
	printf("\n");

}
