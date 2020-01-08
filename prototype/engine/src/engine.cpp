#include <iostream> 
#include <vector>
#include <algorithm>
#include <fstream> 
#include <string>

#include "../proto/config.pb.h"
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

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
    msgType::IPL_Engine engine; 
}