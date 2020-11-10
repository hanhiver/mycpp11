#include <iostream> 
#include <string> 
#include <cpuid.h>
#include <stdio.h>

char cpuid[512] = {0};

std::string cpu_id()
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
    std::string ret(cpuid);
    return ret;
}


bool get_cpu_id(std::string& cpu_id)
{
    int ax, bx, cx, dx;
    int level;
    int level_max = 3;
    int len = 0;
    int size; 

    for (level = 0; level < level_max; ++level)
    {
        __cpuid(level, ax, bx, cx, dx);

        if (0 == level)
        {
            size = sprintf(cpuid + len, "%08X", ax);
        }
        else if (1 == level)
        {
            size = sprintf(cpuid + len, "%08X-%08X-%08X", ax, cx, dx);
        }
        else if (2 == level)
        {
            size = sprintf(cpuid + len, "%08X-%08X-%08X", ax, bx, dx);
        }

        len += size;
        cpuid[len] = '_';
        ++len;
    }
    cpuid[len - 1] = 0;

    std::string(cpuid).swap(cpu_id);
    return true;
}

int main (void)
{
  int a, b, c, d;
  __cpuid (0 /* vendor string */, a, b, c, d);
  printf ("EAX: %x\nEBX: %x\nECX: %x\nEDX: %x\n", a, b, c, d);

  std::cout << "CPUID: " << cpu_id() << std::endl;

  std::string cpuid;
  get_cpu_id(cpuid);
  std::cout << "CPUID: " << cpuid << std::endl;
  return 0;
}
