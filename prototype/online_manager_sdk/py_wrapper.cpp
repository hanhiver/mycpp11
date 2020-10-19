#include <iostream> 
#include "sdk_manager.hpp"

extern "C"
{

void test(const char* input)
{
    std::string name(input);
    std::cout << "Hello, " << name << std::endl; 
}

AUTH_CODE SDKM_Init(const char* config_file_path)
{
    std::string str(config_file_path);
    AUTH_CODE ret = SDKManager::Get().Init(str);
    return ret; 
}

bool SDKM_Auth()
{
    bool ret = SDKManager::Get().Auth();
    return ret;
} 

void SDKM_Count(const char* func_name, unsigned int call_count)
{
    std::string str(func_name);
    SDKManager::Get().Count(str, call_count);
}

void SDKM_Shutdown()
{
    SDKManager::Get().Shutdown();
}

} // extern "C"