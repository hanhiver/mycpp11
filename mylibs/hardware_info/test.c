#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main(int aargc, char* argv[])
{
         struct in_addr addr1,addr2;
         unsigned long   ip1,ip2;
         ip1= inet_addr("192.168.1.7");
         ip2 = inet_addr("192.168.1.2");
         memcpy(&addr1, &ip1, 4);
         memcpy(&addr2, &ip2, 4);
         printf("%s : %s\n", inet_ntoa(addr1), inet_ntoa(addr2));    //注意不能这样输出


         printf("%s\n", inet_ntoa(addr1));
         printf("%s\n", inet_ntoa(addr2));
         return 0;
}


