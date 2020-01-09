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

int main(int argc, char** argv)
{   
    if (!Params::Get().ParaseParamsFile("config.cfg"))
    {
        std::cerr << "Failed to read configuration file. " << std::endl; 
        return EXIT_FAILURE;
    }

    Params::Get().PrintParams();
}