#include <stdio.h>
#include "get_cpuid.h"

int main()
{
    char* cpuid = get_cpu_id_c();
    if (NULL == cpuid)
    {
        printf("Failed to get hardware info. \n");
        return -1;
    }
    printf("CPUID for 1st core is: %s\n", cpuid);
    return 0; 
}