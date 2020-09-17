// rsa_test.cpp  
// g++ rsa_test.cpp -o rsa_test -lcrypto  
// 输入命令，生成公钥和私钥（1024位）
// openssl genrsa -out /tmp/prikey.pem 1024
// openssl rsa -in /tmp/prikey.pem -pubout -out /tmp/pubkey.pem

#include <openssl/rsa.h>  
#include <openssl/err.h>  
#include <openssl/pem.h>  
  
#include <iostream>  
#include <string>  
#include <cstring>  
#include <cassert>  
using namespace std;  
  
//加密  
std::string EncodeRSAKeyFile( const std::string& strPemFileName, const std::string& strData )  
{  
    if (strPemFileName.empty() || strData.empty())  
    {  
        assert(false);  
        return "";  
    }  
    FILE* hPubKeyFile = fopen(strPemFileName.c_str(), "rb");  
    if( hPubKeyFile == NULL )  
    {  
        assert(false);  
        return "";   
    }  
    std::string strRet;  
    RSA* pRSAPublicKey = RSA_new();  
    if(PEM_read_RSA_PUBKEY(hPubKeyFile, &pRSAPublicKey, 0, 0) == NULL)  
    {  
        assert(false);  
        return "";  
    }  
  
    int nLen = RSA_size(pRSAPublicKey);  
    char* pEncode = new char[nLen + 1];  
    int ret = RSA_public_encrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)pEncode, pRSAPublicKey, RSA_PKCS1_PADDING);  
    if (ret >= 0)  
    {  
        strRet = std::string(pEncode, ret);  
    }  
    delete[] pEncode;  
    RSA_free(pRSAPublicKey);  
    fclose(hPubKeyFile);  
    CRYPTO_cleanup_all_ex_data();   
    return strRet;  
}  
  
//解密  
std::string DecodeRSAKeyFile( const std::string& strPemFileName, const std::string& strData )  
{  
    if (strPemFileName.empty() || strData.empty())  
    {  
        assert(false);  
        return "";  
    }  
    FILE* hPriKeyFile = fopen(strPemFileName.c_str(),"rb");  
    if( hPriKeyFile == NULL )  
    {  
        assert(false);  
        return "";  
    }  
    std::string strRet;  
    RSA* pRSAPriKey = RSA_new();  
    if(PEM_read_RSAPrivateKey(hPriKeyFile, &pRSAPriKey, 0, 0) == NULL)  
    {  
        assert(false);  
        return "";  
    }  
    int nLen = RSA_size(pRSAPriKey);  
    char* pDecode = new char[nLen+1];  
  
    int ret = RSA_private_decrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)pDecode, pRSAPriKey, RSA_PKCS1_PADDING);  
    if(ret >= 0)  
    {  
        strRet = std::string((char*)pDecode, ret);  
    }  
    delete [] pDecode;  
    RSA_free(pRSAPriKey);  
    fclose(hPriKeyFile);  
    CRYPTO_cleanup_all_ex_data();   
    return strRet;  
}  
  
int main()  
{  
    //原文  
    const string one = "Hello, I shall be enscapted. ";  
    cout << "Original Msg: " << one << endl;  
  
    //密文（二进制数据）  
    string two = EncodeRSAKeyFile("/tmp/pubkey.pem", one);  
    cout << "Enscaped Msg: " << two << endl;  
  
    //顺利的话，解密后的文字和原文是一致的  
    string three = DecodeRSAKeyFile("/tmp/prikey.pem", two);  
    cout << "Recovered Msg: " << three << endl;  
    return 0;  
}  
