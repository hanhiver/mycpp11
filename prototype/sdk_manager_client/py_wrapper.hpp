#include "sdk_manager.hpp"

extern "C"
{

AUTH_CODE SDKM_Init(const std::string& config_file_path);

bool SDKM_Auth();

void SDKM_Count(const std::string func_name, unsigned int call_count);

void SDKM_Shutdown();

}  // extern "C"