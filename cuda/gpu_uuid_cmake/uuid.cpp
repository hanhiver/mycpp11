#include <cuda_runtime.h>
//#include <helper_cuda.h>

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <sstream>
#include <memory.h>

int *pArgc = NULL;
char **pArgv = NULL;

bool get_1st_gpu_uuid(std::string& uuid)
{
    int deviceCount = 0; 
    cudaError_t error_id = cudaGetDeviceCount(&deviceCount);
    if (error_id != cudaSuccess)
    {
        std::cerr << "cudaGetDeviceCount error. " << std::endl;
        return false; 
    }
    
    int dev = 0;
    cudaSetDevice(dev);
    cudaDeviceProp deviceProp;
    cudaGetDeviceProperties(&deviceProp, dev);

    int uuid_array[16] = {0}; 
    for (int i = 0; i < 16; i++)
    {
        memcpy(&uuid_array[i], deviceProp.uuid.bytes + i, 1);
    }

    std::stringstream ss; 
    ss << std::hex << std::setfill('0')
        << std::setw(2) << uuid_array[0]
        << std::setw(2) << uuid_array[1]
        << std::setw(2) << uuid_array[2]
        << std::setw(2) << uuid_array[3] << '-'
        << std::setw(2) << uuid_array[4]
        << std::setw(2) << uuid_array[5] << '-'
        << std::setw(2) << uuid_array[6]
        << std::setw(2) << uuid_array[7] << '-'
        << std::setw(2) << uuid_array[8]
        << std::setw(2) << uuid_array[9] << '-'
        << std::setw(2) << uuid_array[10]
        << std::setw(2) << uuid_array[11]
        << std::setw(2) << uuid_array[12]
        << std::setw(2) << uuid_array[13]
        << std::setw(2) << uuid_array[14]
        << std::setw(2) << uuid_array[15];

    uuid = ss.str();

    return true;
}
