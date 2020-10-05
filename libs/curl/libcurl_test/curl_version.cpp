#include <iostream>
#include <curl/curl.h>

int main(void)
{
    std::cout << "CURL VERSION: " << curl_version() << std::endl;
    return 0;
}