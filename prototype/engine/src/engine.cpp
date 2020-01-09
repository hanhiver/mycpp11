#include <iostream> 
#include <vector>
#include <algorithm>
#include <fstream> 
#include <string>

//#include "config.pb.h"
//#include <google/protobuf/text_format.h>
//#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <fcntl.h> 
#include <stdlib.h> 
#include <stdio.h> 

#include "core/params.hpp"
#include "core/init.hpp"

int main(int argc, char** argv)
{   
    if (GlobalInit(&argc, &argv) != 0)
    {
        return EXIT_FAILURE;
    }
    
    auto params = Params::Get();
    //std::cout << "Print configures: " << std::endl; 
    //params.PrintParams();

    auto sys_params = Params::Get().GetSystemParams();
    auto camera_params = Params::Get().GetCameraParams();
    auto ipl_engine_params = Params::Get().GetIPLEngineParams();
    auto display_device_params = Params::Get().GetDisplayDeviceParams(); 

    std::cout << "\nsys_params: " << std::endl; 
    sys_params.PrintDebugString();

    std::cout << "\ncamera_params: " << std::endl; 
    camera_params.PrintDebugString();

    std::cout << "\nipl_engine_params: " << std::endl; 
    ipl_engine_params.PrintDebugString(); 

    return 0; 
}