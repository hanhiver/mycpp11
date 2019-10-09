#include <uuid/uuid.h>
#include <iostream>
#include <string> 

int main()
{
    char buf[200];
    uuid_t uu;

    uuid_generate(uu);
    uuid_unparse(uu, buf);
    std::string uu_str = std::string(buf, 36);

    printf("{");
    for (int i=0; i<15; ++i)
    {
        printf("%02X-", uu[i]);
    }
    printf("%02X}\n", uu[15]);

    std::cout << "UUID: " << uu_str << std::endl; 
    return 0;
}
