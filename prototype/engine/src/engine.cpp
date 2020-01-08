#include <iostream> 
#include <vector>
#include <algorithm>
#include <fstream> 
#include <string>

#include "../proto/config.pb.h"
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

//#include <unistd.h> 
//#include <string.h> 
//#include <errno.h> 
//#include <sys/types.h> 
//#include <sys/stat.h>
#include <fcntl.h> 
#include <stdlib.h> 
#include <stdio.h> 

int main(int argc, char** argv)
{
    int fd = open("config.cfg", O_RDONLY);
    if (fd<0)
    {
        std::cerr << "File config.cfg open failed. " << std::endl;
        return EXIT_FAILURE;
    }

    google::protobuf::io::FileInputStream fileInput(fd);
    fileInput.SetCloseOnDelete(true);
    ws_engine::PointParameter engine; 
    std::cout << "Read config file: " << std::endl; 
    google::protobuf::TextFormat::Parse(&fileInput, &engine);
    engine.PrintDebugString();
}