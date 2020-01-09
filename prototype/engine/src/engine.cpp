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
    std::cout << "Print configures: " << std::endl; 
    params.PrintParams();
}