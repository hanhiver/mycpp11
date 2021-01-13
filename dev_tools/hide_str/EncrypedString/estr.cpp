#include <iostream> 
#include <string> 

std::string DecryptString(std::string RawStr)
{
    std::string DecryptedStr ="";
    for (int i = 0; i < RawStr.size(); i++)
    {
        DecryptedStr += (char)((int)RawStr[i] - 80 + i);
    }

    return DecryptedStr;
}

std::string EncryptString(std::string RawStr)
{
    std::string EncryptedStr ="";
    for (int i = 0; i < RawStr.size(); i++)
    {
        EncryptedStr += (char)((int)RawStr[i] + 80 - i);
    }

    return EncryptedStr;
}

int main()
{
    std::string encrypted = EncryptString("Test");
    std::cout << encrypted << std::endl;
    std::cout << DecryptString(encrypted) << std::endl;

    return 0;
}