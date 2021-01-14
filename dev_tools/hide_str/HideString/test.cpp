#include <iostream> 
#include <string> 
#include "estring.h"
#include "pub.h"

DEFINE_ESTRING(EncryptionKey, 0x7f, ('M')('y')(' ')('s')('t')('r')('o')('n')('g')(' ')('e')('n')('c')('r')('y')('p')('t')('i')('o')('n')(' ')('k')('e')('y'))
DEFINE_ESTRING(EncryptionKey2, 0x27, ('T')('e')('s')('t'))

int main()
{
    //std::string pub_str = "";
    //pub_str += std::string("hello");
    std::cout << GetEstring_EncryptionKey() << std::endl;
    std::cout << GetEstring_EncryptionKey2() << std::endl;
    std::cout << GetEstring_pub() << std::endl;
    return 0;
}
