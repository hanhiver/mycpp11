#include <iostream> 
#include <string> 

#include "chttpclient.h"

int main(int argc, char* argv[])
{
    CHttpClient client; 
    std::string response; 
    int res = client.Get("http://www.baidu.com", response);
    if (res == 0)
    {
        std::cout << response << std::endl;
    }
    else
    {
        std::cout << "Failed to connect the URL. " << std::endl;
        return -1; 
    }

    return 0;
}