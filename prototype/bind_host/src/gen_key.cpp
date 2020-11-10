#include "bind_host.hpp"
#include <iostream>
#include <fstream>

#include "version.h"
#include "params.hpp"
#include "tools.hpp"
#include "base64.hpp"
#include "COpenSSL.hpp"

// 用字符串在client sdk中标记出具体的版本和build时间信息。
const char* bind_host_version = BIND_HOST_VERSION;
const char* bind_host_build_time = BIND_HOST_BUILD_TIME;

bool GenKey(const std::string& app_name)
{
    std::string cpu_id; 
    bool res = get_cpu_id(cpu_id);
    if (false == res)
    {
        std::cerr << "Failed to get hardware info. " << std::endl;
        return false;
    }

    std::cout << "Hardware info: \n" << cpu_id << std::endl;

    COpenSSL openssl; 
    std::cout << "App Name: \n" << app_name << std::endl; 
    std::string encript_text = openssl.signMessage(openssl.privateKey, cpu_id + app_name);
    std::cout << "Access Key: \n" << encript_text << std::endl;

    std::ofstream key_file;
    key_file.open("key.conf", std::ios::out| std::ios_base::ate);
    if (!key_file.is_open())
    {
        std::cerr << "Failed to open key.conf to write." << std::endl;
        return false;
    }

    key_file << "key_info {\n"
         << "\tapp_name: " << "\"" << app_name << "\"\n"
         << "\tkey: " << "\"" << encript_text << "\"\n"
         << "}\n";

    key_file.flush();
    key_file.close();

    return true; 
}

int main(int argc, char* argv[])
{
    if (2 != argc)
    {
        std::cout << "Usage: " << argv[0] << " app_name " << std::endl;
        return 0;
    }

    std::string app_name {argv[1]};
    GenKey(app_name);

    return 0;
}

