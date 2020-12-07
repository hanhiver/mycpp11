// 请确保接下来两句按照正确的顺序连接在一起
// 否则的话，cpu_affinity可能无法正常工作
// gcc -g -o stest stest.c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <cpuid.h>
#include <string.h>

int main()
{
    // 下面这两句，随便让一句运行，整个程序就能正常运行，
    // 否则就在最后的printf崩溃，应该是在涉及到计算字符串长度的地方。
    //printf("test.\n");
    //puts("\0");
    
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

    // 崩溃会出现在这一句。
    printf("hello world!\n");
    
}