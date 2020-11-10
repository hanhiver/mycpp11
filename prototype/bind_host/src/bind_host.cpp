#include "bind_host.hpp"
#include <iostream> 

#include "version.h"
#include "params.hpp"
#include "tools.hpp"
#include "base64.hpp"
#include "COpenSSL.hpp"

// 用字符串在client sdk中标记出具体的版本和build时间信息。
const char* bind_host_version = BIND_HOST_VERSION;
const char* bind_host_build_time = BIND_HOST_BUILD_TIME;

bool BindCheck(const std::string& key_path)
{
    // 读取配置文件，读取失败则初始化失败。
    bool res = Params::Get().ParaseParamsFile(key_path);
    if (false == res)
    {
        std::cerr << "Failed to load config file: " << key_path << std::endl;
        return false;
    }

    Params::Get().PrintParams();

    std::string cpu_id; 
    res = get_cpu_id(cpu_id);
    if (false == res)
    {
        std::cerr << "Failed to get hardware info. " << std::endl;
        return false;
    }

    //std::cout << "Hardware info: \n" << cpu_id << std::endl;

    std::string encript_text = Params::Get().GetKeyInfo().key();
    std::string app_name = Params::Get().GetKeyInfo().app_name();
    //std::cout << "Key: \n" << encript_text << std::endl;

    COpenSSL openssl;
    res = openssl.verifySignature(openssl.publicKey, cpu_id + app_name, encript_text);

    return res; 
}
