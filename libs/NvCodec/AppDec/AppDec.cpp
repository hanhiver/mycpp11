#include <iostream> 
#include <algorithm> 
#include <thread> 
#include "NvDecoder/NvDecoder.h"
#include "../Utils/NvCodecUtils.h"
#include "../Utils/FFmpegDemuxer.h"

inline bool mycheck(int e, int iLine, const char *szFile) {
    if (e < 0) {
        std::cerr << "General error " << e << " at line " << iLine << " in file " << szFile;
        return false;
    }
    return true;
}

#define chk(call) mycheck(call, __LINE__, __FILE__)


int main(int argc, char** argv)
{
    chk(cuInit(0));
    int nGpu = 0; 
    chk(cuDeviceGetCount(&nGpu)); 
    std::cout << "There are " << nGpu << " GPUs in the system. " << std::endl; 

    CUdevice cuDevice = 0; 
    chk(cuDeviceGet(&cuDevice, 0));
    char szDeviceName[80]; 
    chk(cuDeviceGetName(szDeviceName, sizeof(szDeviceName), cuDevice));
    std::cout << "GPU in use: " << szDeviceName << std::endl; 

    CUcontext cuContext = NULL; 
    chk(cuCtxCreate(&cuContext, 0, cuDevice));

    char szInFilePath = "/home/dhan/1s.mp4";
    char szOutFilePath = "/tmp/1s.mp4";
    

}