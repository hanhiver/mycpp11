#include <vector> 
#include <algorithm>
#include <fstream> 
#include <string> 

#include "../config.pb.h"
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h> 

class Params
{
public:
    static Params& Get()
    {
        static Params instance; 
        return instance;
    }

    bool ParaseParamsFile(std::string filename);
    
    inline static const ws_engine::SystemParameter& GetSystemParams()
    {
        return params_.sys_params();
    }

    inline static const ws_engine::CameraParameter& GetCameraParams()
    {
        return params_.camera();
    }

    inline static const ws_engine::IPL_Engine& GetIPLEngineParams()
    {
        return params_.ipl_engine();
    }

    inline static const ws_engine::DisplayDevice& GetDisplayDeviceParams()
    {
        return params_.display_device();
    }

    void PrintParams();

private: 
    Params() {};
    static ws_engine::WsEngineParameters params_;
};