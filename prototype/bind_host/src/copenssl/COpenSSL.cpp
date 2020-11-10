#include "COpenSSL.hpp"
using namespace std; 

COpenSSL::COpenSSL()
{
    // RSA key pairs for test. 
	privateKey = "-----BEGIN RSA PRIVATE KEY-----\n"\
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
		"-----END RSA PRIVATE KEY-----\n\0";

	publicKey = "-----BEGIN PUBLIC KEY-----\n"\
		"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDT3YXzRLSdzbNpNS8QfujfY33M\n"\
		"pONEPVMYsDzDIhSVuWvYYy6cnmzSZrWsWLa6vrdZur0Gsf4tKJsZwVeWgXIiD0fu\n"\
		"D+s2jxgR731jbsYoeAZuNqoV40YAvsHDPb/fDHlB8MzbxkRVJwLQo1DGrbF6b1J+\n"\
		"Rv9wCDn47zBJYvrheQIDAQAB\n"\
		"-----END PUBLIC KEY-----\n\0";
}


COpenSSL::~COpenSSL()
{
}

void COpenSSL::md5(const std::string& srcStr, std::string& encodedHexStr)
{
	// call md5 hash.    
	unsigned char mdStr[33] = { 0 };
	MD5((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);

	// Hex chars 32bytes after hash. 
	char buf[65] = { 0 };
	char tmp[3] = { 0 };
	for (int i = 0; i < 32; i++)
	{
		sprintf(tmp, "%02x", mdStr[i]);
		strcat(buf, tmp);
	}
	buf[32] = '\0'; // '\0' after 32 chars.
	encodedHexStr = std::string(buf);
}
  
void COpenSSL::sha256(const std::string& srcStr, std::string& encodedHexStr)
{
	// call sha256 hash.    
	unsigned char mdStr[65] = { 0 };
	SHA256((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);

	// Hex chars 32bytes after hash. 
	char buf[129] = { 0 };
	char tmp[3] = { 0 };
	for (int i = 0; i < 32; i++)
	{
		sprintf(tmp, "%02x", mdStr[i]);
		strcat(buf, tmp);
	}
	buf[128] = '\0'; // '\0' after 128 chars.
	encodedHexStr = std::string(buf);
}

void COpenSSL::sha384(const std::string& srcStr, std::string& encodedHexStr)
{
	// call sha256 hash.    
	unsigned char mdStr[97] = { 0 };
	SHA384((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);

	// Hex chars 48bytes after hash. 
	char buf[385] = { 0 };
	char tmp[3] = { 0 };
	for (int i = 0; i < 48; i++)
	{
		sprintf(tmp, "%02x", mdStr[i]);
		strcat(buf, tmp);
	}
	buf[384] = '\0'; // '\0' after 256 chars.
	encodedHexStr = std::string(buf);
}

void COpenSSL::sha512(const std::string& srcStr, std::string& encodedHexStr)
{
	// call sha256 hash.    
	unsigned char mdStr[129] = { 0 };
	SHA512((const unsigned char *)srcStr.c_str(), srcStr.length(), mdStr);

	// Hex chars 64bytes after hash. 
	char buf[257] = { 0 };
	char tmp[3] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		sprintf(tmp, "%02x", mdStr[i]);
		strcat(buf, tmp);
	}
	buf[256] = '\0'; // '\0' after 256 chars.
	encodedHexStr = std::string(buf);
}

std::string COpenSSL::des_encrypt(const std::string& clearText, const std::string& key)
{
    // encripted string.
	std::string cipherText;

	DES_cblock keyEncrypt;
	memset(keyEncrypt, 0, 8);

	// Establish the key with certain length. 
	if (key.length() <= 8)
		memcpy(keyEncrypt, key.c_str(), key.length());
	else
		memcpy(keyEncrypt, key.c_str(), 8);

	// switch the key. 
	DES_key_schedule keySchedule;
	DES_set_key_unchecked(&keyEncrypt, &keySchedule);

	// encription loop, 8 bytes each time. 
	const_DES_cblock inputText;
	DES_cblock outputText;
	std::vector<unsigned char> vecCiphertext;
	unsigned char tmp[8];

	for (unsigned int i = 0; i < clearText.length() / (unsigned int)8; i++)
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
		// encription function. 
		DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
		memcpy(tmp, outputText, 8);

		for (int j = 0; j < 8; j++)
			vecCiphertext.push_back(tmp[j]);
	}

	cipherText.clear();
	cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());

	return cipherText;
}

std::string COpenSSL::des_decrypt(const std::string& cipherText, const std::string& key)
{
    // clear text. 
	std::string clearText; 

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

	for (unsigned int i = 0; i < cipherText.length() / 8; i++)
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
		// decription function. 
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
	// key pair. 
	size_t pri_len;
	size_t pub_len;
	char *pri_key = NULL;
	char *pub_key = NULL;

	// generate key pair. 
	// deprecated: 
	// RSA *keypair = RSA_generate_key(KEY_LENGTH, RSA_3, NULL, NULL);
	RSA* keypair = RSA_new();
	BIGNUM* bne = BN_new();
	BN_set_word(bne, RSA_3);
	int res = RSA_generate_key_ex(keypair, KEY_LENGTH, bne, NULL);
	if (res != 1)
	{
        assert(false);
		return;
	}

	BIO *pri = BIO_new(BIO_s_mem());
	BIO *pub = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
	// PEM_write_bio_RSAPublicKey(pub, keypair); // Write pub key with pkcs1 format. 
	PEM_write_bio_RSA_PUBKEY(pub, keypair); // write pub key with pkcs8 format. 

	// get length. 
	pri_len = BIO_pending(pri);
	pub_len = BIO_pending(pub);

	// read key pair. 
	pri_key = (char *)malloc(pri_len + 1);
	pub_key = (char *)malloc(pub_len + 1);

	BIO_read(pri, pri_key, pri_len);
	BIO_read(pub, pub_key, pub_len);

	pri_key[pri_len] = '\0';
	pub_key[pub_len] = '\0';

	// store the key pair. 
	strKey[0] = pub_key;
	strKey[1] = pri_key;

	// save the key pare to files. 
	// File will be (start with rsa public key/ begin rsa private key) 
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

	RSA_free(keypair);
	BIO_free_all(pub);
	BIO_free_all(pri);

	free(pri_key);
	free(pub_key);
}

bool COpenSSL::rsa_verify_pubkey(const std::string& pubKey)
{
	RSA *rsa = NULL;
	BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);
	rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL); 

	if (rsa == NULL)
		return false;
	else
		return true;
}

bool COpenSSL::rsa_verify_prikey(const std::string& priKey)
{
	RSA *rsa = NULL;
	BIO *keybio;
	keybio = BIO_new_mem_buf((unsigned char *)priKey.c_str(), -1);
	rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
	
	if (rsa == NULL)
		return false;
	else
		return true;
}

std::string COpenSSL::rsa_pub_encrypt(const std::string& clearText, const std::string& pubKey)
{
	std::string strRet;
	RSA *rsa = RSA_new();
	BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);
	
	// Here we have 3 metheod:
	// 1. Read the key pair from memory, then generate the rsa in memory. 
	// 2. Read the key pair from file, then generate the rsa in memory.
	// 3. Generate rsa directly in memory.  
	// -----BEGIN RSA PUBLIC KEY----- 
	// rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL); // If the key is PKCS1 format
	// -----BEGIN PUBLIC KEY-----
	rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL); // If the key is is PKCS8 format

	int len = RSA_size(rsa);
	char *encryptedText = (char *)malloc(len + 1);
	memset(encryptedText, 0, len + 1);

	// encrypt function.  
	int ret = RSA_public_encrypt(clearText.length(), (const unsigned char*)clearText.c_str(), (unsigned char*)encryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = std::string(encryptedText, ret);

	free(encryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}

std::string COpenSSL::rsa_pri_decrypt(const std::string& cipherText, const std::string& priKey)
{
	std::string strRet;
	RSA *rsa = RSA_new();
	BIO *keybio;
	keybio = BIO_new_mem_buf((unsigned char *)priKey.c_str(), -1);

	// Here we have 3 metheod:
	// 1. Read the key pair from memory, then generate the rsa in memory. 
	// 2. Read the key pair from file, then generate the rsa in memory.
	// 3. Generate rsa directly in memory.  
	// -----BEGIN RSA PRIVATE KEY-----
	rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL); // Ensure the key is PKCS1 format

	int len = RSA_size(rsa);
	char *decryptedText = (char *)malloc(len + 1);
	memset(decryptedText, 0, len + 1);

	// decript function. 
	int ret = RSA_private_decrypt(cipherText.length(), (const unsigned char*)cipherText.c_str(), (unsigned char*)decryptedText, rsa, RSA_PKCS1_PADDING);
	if (ret >= 0)
		strRet = std::string(decryptedText, ret);

	free(decryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return strRet;
}

std::string COpenSSL::signMessage(const std::string& privateKey, const std::string& plainText)
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

bool COpenSSL::verifySignature(const std::string& publicKey, const std::string& plainText, const std::string& signatureBase64)
{
	RSA* publicRSA = createPublicRSA(publicKey);
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
	EVP_MD_CTX_reset(m_RSASignCtx);
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

std::string COpenSSL::readKeyFile(const std::string& filename)
{
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
