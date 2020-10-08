#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

//include "config.pb.h"
//#include <google/protobuf/text_format.h>
//#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include "params.hpp"

int main(int argc, char** argv)
{
    
    auto params = Params::Get();
    params.ParaseParamsFile("../test.config");

    //auto sys_params = Params::Get().GetSystemParams();
    //auto key_info = Params::Get().GetKeyInfo();
    auto sys_params = params.GetSystemParams();
    auto key_info = params.GetKeyInfo();

    std::cout << "\nsys_params: " << std::endl;
    sys_params.PrintDebugString();

    std::cout << "\nkey_info: " << std::endl;
    key_info.PrintDebugString();
    
    std::cout << "Done. " << std::endl;
    return 0;
}