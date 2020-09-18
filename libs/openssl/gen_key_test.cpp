// gcc -o gen_key_test.out gen_key_test.cpp -lcrypto
#include <stdio.h>
#include "openssl/rsa.h"
int main()
{
    RSA *rsa = RSA_new();
    int ret = 0;
    BIGNUM* bne = BN_new();
    ret=BN_set_word(bne,RSA_F4);
    ret = RSA_generate_key_ex(rsa,512,bne,NULL);
    if(ret!=1)
    {
        printf("Error to generate key. \n");
        return -1; 
    }
    else
    {
        printf("Generate key pair done. \n");
        return 0;
    }
}