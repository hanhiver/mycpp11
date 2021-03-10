#include <stdlib.h>
#include <Winsock2.h>
#include <Iptypes.h>
#include <iphlpapi.h>
#include <stdio.h>

static void PrintMACaddress(unsigned char MACData[])
{
    printf("MAC Address: %02X-%02X-%02X-%02X-%02X-%02X\n",
    MACData[0], MACData[1],MACData[2],MACData[3],MACData[4],MACData[5]);
}

static void GetMacAddress(void)
{

    IP_ADAPTER_INFO AdapterInfo[16];
    DWORD dwBuflen = sizeof(AdapterInfo);

    DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBuflen);

    PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;

    do{
        PrintMACaddress(pAdapterInfo->Address);
        pAdapterInfo = pAdapterInfo->Next;
    }while(pAdapterInfo);

}

int main()
{
    GetMacAddress();
    system("pause");
    return 0;
}