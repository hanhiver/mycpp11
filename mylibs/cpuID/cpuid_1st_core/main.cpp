// gcc -c get_cpuid.c; ar -r libget_cpuid.a get_cpuid.o; g++ -o main main.o -L./ -lget_cpuid
#include <iostream> 
#include <string> 
#include "get_cpuid.h"

int main()
{
    char* cpuid = get_cpu_id_c();
    if (NULL != cpuid)
    {
        printf("Failed to get hardware info. \n");
        return -1;
    }
    std::string id(cpuid);
    std::cout << "CPUID for 1st core is: " << id << std::endl;
    return 0; 
}