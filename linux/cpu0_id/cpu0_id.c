// 请确保接下来两句按照正确的顺序连接在一起
// 否则的话，cpu_affinity可能无法正常工作
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <cpuid.h>
#include <string.h>

//char cpuid[512] = {0};

//char* get_cpu_id_c()
int get_cpu_id_c(char* cpu_id)
{
    char cpuid[512] = {'\0'};

    // 创建绑定cpu运行的数据结构。
    cpu_set_t* cpusetp;
    int num_cpus = 1;
    size_t cpuset_size;

    // 获取当前系统中配置的cpu个数。
    num_cpus = sysconf(_SC_NPROCESSORS_CONF);

    // 分配满足cpu个数的空间。
    cpusetp = CPU_ALLOC(num_cpus); 
    //printf("There are %d cpus in the system. \n", num_cpus);
    if (NULL == cpusetp)
    {
        perror("CPU_ALLOC");
        //exit(EXIT_FAILURE);
        return -1;
    }
    cpuset_size = CPU_ALLOC_SIZE(num_cpus);

    // 清空结构，并将第一个cpu放进结构。
    CPU_ZERO_S(cpuset_size, cpusetp);
    CPU_SET_S(0, cpuset_size, cpusetp);
    
    // 设置本进程在第一个cpu中运行。
    if (sched_setaffinity(0, CPU_SETSIZE, cpusetp) == -1)
    {
        printf("failed to set thread affinity, exit...\n");
        //exit(EXIT_FAILURE);
        return -1;
    }
    
    // 设置cpuid获取的相关变量。
    int ax, bx, cx, dx;
    int level;
    int level_max = 3;
    int len = 0;
    int size; 

    // 获取完整的cpuid。
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
    cpuid[len - 1] = '\0';
    memcpy(cpu_id, cpuid, 512);
    
    return 0;
}

int main()
{
    char mycpuid[512] = {'\0'};

    int res = get_cpu_id_c(mycpuid);
    if (0 == res)
    {
        printf("CPU0's ID: %s\n", mycpuid);
    }
    else
    {
        printf("Failed to get CPUID. \n");
    }
}