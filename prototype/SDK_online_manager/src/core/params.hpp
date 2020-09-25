#ifndef DAMO_SDK_ONLINE_MANAGER_PARAMS_HPP
#define DAMO_SDK_ONLINE_MANAGER_PARAMS_HPP

#include <vector> 
#include <algorithm>
#include <fstream> 
#include <string> 

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <fcntl.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "../config.pb.h"

class Params
{
public: 
    static Params& Get()
    {
        static Params instance; 
        return instance; 
    }

    bool ParaseParamsFile(std::string filename);

    inline static const sdk_online_manager::SystemParams& GetSystemParams()
    {
        return mParams.sys_params();
    }

    inline static const sdk_online_manager::KeyInfo& GetKeyInfo()
    {
        return mParams.key_info();
    }
    
    void PrintParams();

private: 
    Params::Params() {}
    static sdk_online_manager::ClientParams mParams; 
};

#endif  // DAMO_SDK_ONLINE_MANAGER_PARAMS_HPP