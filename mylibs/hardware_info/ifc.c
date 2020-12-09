#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

int main()
{
    int i=0;
    int sockfd;
    struct ifconf ifconf;
    unsigned char buf[1024];
    struct ifreq *ifreq;
    struct ifreq freq; 
    unsigned char hd[10];

    //初始化ifconf
    ifconf.ifc_len = 1024;
    ifconf.ifc_buf = buf;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        perror("socket");
        exit(1);
    }
    ioctl(sockfd, SIOCGIFCONF, &ifconf);    //获取所有接口信息


    //接下来一个一个的获取IP地址
    ifreq = (struct ifreq*)buf;
    for(i=(ifconf.ifc_len/sizeof(struct ifreq)); i>0; i--)
    {
        if(ifreq->ifr_flags == AF_INET)             //for ipv4
        {
            //printf("name=[%s], ifr_flags=[%s]\n", ifreq->ifr_name, ifreq->ifr_hwaddr.sa_data);
            memcpy(&freq, ifreq, sizeof(freq));
            ioctl(sockfd, SIOCGIFHWADDR, &freq);
            printf("name=[%s]\n", freq.ifr_name);
            memcpy(hd, freq.ifr_hwaddr.sa_data, sizeof(hd));
            printf("HWaddr:%02X:%02X:%02X:%02X:%02X:%02X\n\n",hd[0],hd[1],hd[2],hd[3],hd[4],hd[5]); 
            //printf("local addr = [%s]\n",
            //       inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr));
            ifreq++;
        }
    }
    return 0;
}