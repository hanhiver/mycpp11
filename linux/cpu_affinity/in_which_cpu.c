#define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h> 

int main(int argc, char *argv[])
{
    cpu_set_t *cpusetp;
    size_t size; 
    int num_cpus, cpu;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <num-cpus>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    num_cpus = sysconf(_SC_NPROCESSORS_CONF);
    printf("There is %d cores in the system.\n", num_cpus);
    cpu = atoi(argv[1]);

    cpusetp = CPU_ALLOC(num_cpus);
    if (NULL == cpusetp)
    {
        perror("CPU_ALLOC");
        exit(EXIT_FAILURE);
    }
    size = CPU_ALLOC_SIZE(num_cpus);
    
    CPU_ZERO_S(size, cpusetp);
    CPU_SET_S(cpu, size, cpusetp);
        
    if (sched_setaffinity(0, size, cpusetp) == -1)//获取线程CPU亲和力
    {
        printf("failed to set thread affinity, exit...\n");
        exit(EXIT_FAILURE);
    }
    
    do
    {
        CPU_ZERO(cpusetp);
        if (sched_getaffinity(0, size, cpusetp) == -1)//获取线程CPU亲和力
        {
            printf("failed to get thread affinity, exit...\n");
            exit(EXIT_FAILURE);
        }
        int i;
        for(i = 0; i < num_cpus; ++i)
        {
            if (CPU_ISSET_S(i, size, cpusetp))
            {
                printf("Running in [%d/%d]. \n", i, num_cpus);
            }
        }
        sleep(1);
    } while(1);

    /*
    size = CPU_ALLOC_SIZE(num_cpus);
    CPU_ZERO_S(size, cpusetp);
    for (cpu = 0; cpu < num_cpus; cpu += 2)
    {
        CPU_SET_S(cpu, size, cpusetp);
    }

    printf("CPU_COUNT() of set: %d\n", CPU_COUNT_S(size, cpusetp));
    */
    CPU_FREE(cpusetp);
    exit(EXIT_SUCCESS);
}
