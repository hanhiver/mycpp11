#include <cpuid.h>
#include <stdio.h>

char cpuid[512] = {0};

const char* cpu_id()
{
    int a, b, c, d;
    int level;
    int level_max = 3;
    int len = 0;
    int size; 

    for (level = 0; level < level_max; ++level)
    {
        __cpuid(level, a, b, c, d);

        if (0 == level)
        {
            size = sprintf(cpuid + len, "%08X", a);
        }
        else if (1 == level)
        {
            size = sprintf(cpuid + len, "%08X-%08X-%08X", a, c, d);
        }
        else if (2 == level)
        {
            size = sprintf(cpuid + len, "%08X-%08X-%08X", a, b, d);
        }

        len += size;
        cpuid[len] = '_';
        ++len;
    }
    cpuid[len - 1] = 0;
    return cpuid;
}


int main (void)
{
  int a, b, c, d;
  __cpuid (0 /* vendor string */, a, b, c, d);
  printf ("EAX: %x\nEBX: %x\nECX: %x\nEDX: %x\n", a, b, c, d);

  printf ("CPUID: %s\n", cpu_id());
  return 0;
}
