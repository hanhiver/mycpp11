#include <fstream> 
#include <unistd.h>
#include <fcntl.h>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include "params.hpp"

ws_engine::WsEngineParameters Params::params_;

bool Params::ParaseParamsFile(std::string filename)
{
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1)
    {
        std::cerr << "Failed to open the config file: " 
                  << filename << std::endl; 
        return false; 
    }

    google::protobuf::io::FileInputStream* input = new google::protobuf::io::FileInputStream(fd);
    bool success = google::protobuf::TextFormat::Parse(input, &params_);
    delete input; 
    close(fd);

    return success; 
}

void Params::PrintParams()
{
    params_.PrintDebugString();
}
