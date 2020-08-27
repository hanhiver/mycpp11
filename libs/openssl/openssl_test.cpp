#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "Base64.h"

// 私钥解密 
std::string rsa_pri_decrypt(const std::string &cipherText, const std::string &priKey) 
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

// 公钥解密    
std::string rsa_pub_decrypt(const std::string &cipherText, const std::string &pubKey)  
{  
    std::string strRet;  
    RSA *rsa = RSA_new();
    BIO *keybio= BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);  
    rsa=PEM_read_bio_RSA_PUBKEY(keybio,&rsa,NULL,NULL);
  
    int len = RSA_size(rsa);  
    char *decryptedText = (char *)malloc(len + 1);  
    memset(decryptedText, 0, len + 1);  
  
    // 解密函数  
    int ret = RSA_public_decrypt(cipherText.length(), (const unsigned char*)cipherText.c_str(), (unsigned char*)decryptedText, rsa, RSA_PKCS1_PADDING);  
    if (ret >= 0)  
        strRet = std::string(decryptedText, ret);  
  
    // 释放内存  
    free(decryptedText);  
    BIO_free_all(keybio);  
    RSA_free(rsa);  
  
    return strRet;  
} 
 
int main(int narg,char** args)
{
    string pubKey="\
-----BEGIN PUBLIC KEY-----\n\
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAptoreKuW1O+Bb1u+O0LQ\n\
NAiaj5i0gbqi5uHCfcTxPIScoeidR/FaPFWpG3mHUCd7SfPKlSQ4H4FGwqkPrAJ8\n\
tb6vfNAY7UPlStaWwCASBBBeHRIFySDIFQnIeXTcZqKgvCAkM3kudyKGMGfZyU6v\n\
SUCMUJbvtIKrSBpPFOaPF1EjfsTpcRjRwNUxjInvxyOmegdLSgg/NNV9AxUSpGX4\n\
Fs5j3W4u4bfgoH6WiI7QLeVWpw+ZcynndtihPa2Y5rKgTDq1IYnniaYy+bTlWMPC\n\
us9AjL0qaM0oXKzUByIeA8cWQR99ewSLsEaa7mhpUZ1jg+fDQEqYfgvenfcOe5bn\n\
NQIDAQAB\n\
-----END PUBLIC KEY-----\n";
    string encStr="TgaNSiG6yPkKql3pIW9310IsRpcppl4SIt12kdP3ZwR0wWj65P3I3YCaSrb7+lmJ9N\
mpTmHHzwgvTQN3zM+IRpjQr1iAJZ0C/+2uM0WkPwbZhvlzcr4iZFOfhe6CbPGibu1\
+pRYdkkxgvXT3/0D4hrtzOxMXVYzBLjfd7xXRfVTXGI7FlBGfq6/W+bg3DE3BQbdS\
07eBBRKQ1Jbl/LPIQP40FK5qdvTDeWTG0m/mLRfpavbIw4pMKnc7845xU9ZZVmxcv\
14O7AJYmJat72mGzDVpafx+65aanLMIydSY+dly62XeSRd5ghd1fSaTHlVN4h59YY\
qNPXGxFKTrMvPUDg==";
    Base64 base;
    string encStr2=base.Decode(encStr.c_str(),encStr.length());
    string decStr=rsa_pub_decrypt(encStr2,pubKey);
    printf("---%s---\n",decStr.c_str());
    system("pause");
    return 0;
}
