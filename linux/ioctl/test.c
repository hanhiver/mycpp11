#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cpuid.h>
#include <string.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

static char cpuid[512];

int main()
{
    int len = 0;
    int i = 0;
    int sockfd;
    struct ifconf ifconf;
    unsigned char buf[1024];
    struct ifreq *ifreq;
    struct ifreq freq;
    unsigned char mac[10];

    // 初始化ifconf
    ifconf.ifc_len = 1024;
    ifconf.ifc_buf = buf;

    // 创建socket接口
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }

    //获取所有接口信息
    if (ioctl(sockfd, SIOCGIFCONF, &ifconf) < 0)
    {
        perror("ioctl SIOCGIFCONF");
        return -1;
    }

    //接下来一个一个的获取IP地址
    ifreq = (struct ifreq*)buf;
    for (i = (ifconf.ifc_len/sizeof(struct ifreq)); i > 0; --i)
    {
        if (strcmp(ifreq->ifr_name, "lo") == 0)
        {
            printf("SKIP: %s\n", ifreq->ifr_name);
            ifreq++;
            continue;
        }
        else
        {
            //printf("INET: %s\n", ifreq->ifr_name);
            memcpy(&freq, ifreq, sizeof(freq));
            if (ioctl(sockfd, SIOCGIFHWADDR, &freq) < 0)
            {
                perror("ioctl SIOCGIFHWADDR");
                return -1;
            }
            memcpy(mac, freq.ifr_hwaddr.sa_data, sizeof(mac));
            //sprintf(cpuid + len, "INET: %s, mac: %02X%02X%02X%02X%02X%02X", freq.ifr_name, mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
            printf("INET: %s, mac: %02X:%02X:%02X:%02X:%02X:%02X\n", freq.ifr_name, mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
            len += 12;
			ifreq++;
            continue;
        }
    }

    cpuid[len] = 0;
    //printf("CPUID: %s\n", cpuid);
}

