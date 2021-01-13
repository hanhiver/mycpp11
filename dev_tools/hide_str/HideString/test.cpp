#include <iostream> 
#include "estring.h"

DEFINE_ESTRING(EncryptionKey, 0x7f, ('M')('y')(' ')('s')('t')('r')('o')('n')('g')(' ')('e')('n')('c')('r')('y')('p')('t')('i')('o')('n')(' ')('k')('e')('y'))
DEFINE_ESTRING(EncryptionKey2, 0x27, ('T')('e')('s')('t'))

int main()
{
    std::cout << GetEncryptionKey() << std::endl;
    std::cout << GetEncryptionKey2() << std::endl;

    return 0;
}
