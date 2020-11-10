#include <iostream> 
#include "bind_host.hpp"

extern "C"
{

bool CheckBindHost(const char* key_file_path)
{
    std::string key_file(key_file_path);
    return BindCheck(key_file);
}

}