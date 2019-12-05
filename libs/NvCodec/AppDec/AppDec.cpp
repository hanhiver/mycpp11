#include <iostream> 
#include <algorithm> 
#include <thread> 
#include <iomanip>
#include <cuda.h>
#include "NvDecoder/NvDecoder.h"
#include "../Utils/NvCodecUtils.h"
#include "../Utils/FFmpegDemuxer.h"

simplelogger::Logger *logger = simplelogger::LoggerFactory::CreateConsoleLogger();

inline bool mycheck(int e, int iLine, const char *szFile) {
    if (e < 0) {
        std::cerr << "General error " << e << " at line " << iLine << " in file " << szFile;
        return false;
    }
    return true;
}

#define chk(call) mycheck(call, __LINE__, __FILE__)

void ShowDecoderCapacity()
{
    int nGpu = 0; 
    chk(cuDeviceGetCount(&nGpu)); 

    // Show the decoder capability. 
    std::cout << "=============\nDecoder Capability: \n=============" << std::endl; 
    const char *aszCodecName[] = 
        {"JPEG", "MPEG1", "MPEG2", "MPEG4", "H264", "HEVC", 
        "HEVC", "HEVC", "VC1", "VP8", "VP9", "VP9", "VP9"};
    cudaVideoCodec aeCodec[] = 
        { cudaVideoCodec_JPEG, cudaVideoCodec_MPEG1, cudaVideoCodec_MPEG2, 
        cudaVideoCodec_MPEG4, cudaVideoCodec_H264, cudaVideoCodec_HEVC, 
        cudaVideoCodec_HEVC, cudaVideoCodec_HEVC, cudaVideoCodec_VC1,
        cudaVideoCodec_VP8, cudaVideoCodec_VP9, cudaVideoCodec_VP9, 
        cudaVideoCodec_VP9 };
    int anBitDepthMinus8[] = {0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 2, 4};
    for (int iGpu=0; iGpu<nGpu; ++iGpu)
    {
        CUdevice cuDevice = 0; 
        chk(cuDeviceGet(&cuDevice, iGpu));
        char szDeviceName[80]; 
        chk(cuDeviceGetName(szDeviceName, sizeof(szDeviceName), cuDevice));
        CUcontext cuContext = NULL; 
        chk(cuCtxCreate(&cuContext, 0, cuDevice)); 
        
        std::cout << "GPU " << iGpu << " - " << szDeviceName << std::endl; 
        for (int i=0; i<sizeof(aeCodec)/sizeof(aeCodec[0]); ++i)
        {
            CUVIDDECODECAPS decodeCaps = {}; 
            decodeCaps.eCodecType = aeCodec[i]; 
            decodeCaps.eChromaFormat = cudaVideoChromaFormat_420; 
            decodeCaps.nBitDepthMinus8 = anBitDepthMinus8[i];

            cuvidGetDecoderCaps(&decodeCaps);
            std::cout << "Codec" << " " << std::setw(6) << aszCodecName[i] << 
                " BitDepth:" << "  " << setiosflags(std::ios::left) << std::setw(3) << decodeCaps.nBitDepthMinus8 + 8 << 
                " Supported:" << "  " << setiosflags(std::ios::left) << std::setw(1) << (int)decodeCaps.bIsSupported <<
                " MaxWidth:" << "  " << setiosflags(std::ios::left) << std::setw(6) << decodeCaps.nMaxWidth << 
                " MaxHeight:" << "  " << setiosflags(std::ios::left) << std::setw(6) << decodeCaps.nMaxHeight << 
                " MaxMBCount:" << "  " << setiosflags(std::ios::left) << std::setw(10) << decodeCaps.nMaxMBCount << 
                " MinWidth:" << "  " << setiosflags(std::ios::left) << std::setw(4) << decodeCaps.nMinWidth << 
                " MinHeight:" << "  " << setiosflags(std::ios::left) << std::setw(4) << decodeCaps.nMinHeight << std::endl;
        }

        std::cout << std::endl; 
        chk(cuCtxDestroy(cuContext));
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " [video file] " << std::endl; 
        return 0; 
    }

    // Initialize the device. 
    chk(cuInit(0));
    int nGpu = 0; 
    chk(cuDeviceGetCount(&nGpu)); 
    std::cout << "There are " << nGpu << " GPUs in the system. " << std::endl; 

    //ShowDecoderCapacity(); 

    // Get the first device in the system. 
    CUdevice cuDevice = 0; 
    chk(cuDeviceGet(&cuDevice, 0));
    char szDeviceName[80]; 
    chk(cuDeviceGetName(szDeviceName, sizeof(szDeviceName), cuDevice));
    std::cout << "GPU in use: " << szDeviceName << std::endl; 

    CUcontext cuContext = NULL; 
    chk(cuCtxCreate(&cuContext, 0, cuDevice));

    //const char* szInFilePath = "/home8/dhan/out.h264";
    char* szInFilePath = argv[1];
    const char* szOutFilePath = "/tmp/out.h264";
    
    std::cout << szInFilePath << std::endl; 
    std::cout << szOutFilePath << std::endl; 
    
    std::ofstream fpOut(szOutFilePath, std::ios::out | std::ios::binary);
    if (!fpOut)
    {
        std::ostringstream err; 
        err << "Unable to open output file: " << szOutFilePath << std::endl; 
        throw std::invalid_argument(err.str());
    }
    
    Rect cropRect = {200, 100, 1480, 820}; 
    Dim resizeDim = {}; 

    FFmpegDemuxer demuxer(szInFilePath); 
    NvDecoder dec(cuContext, demuxer.GetWidth(), demuxer.GetHeight(), false, 
                  FFmpeg2NvCodecId(demuxer.GetVideoCodec()), 
                  NULL, false, false, &cropRect, &resizeDim); 
    
    int nVideoBytes = 0;
    int nFrameReturned = 0; 
    int nFrame = 0; 
    uint8_t* pVideo = NULL;
    uint8_t** ppFrame; 

    do 
    {
        demuxer.Demux(&pVideo, &nVideoBytes);
        dec.Decode(pVideo, nVideoBytes, &ppFrame, &nFrameReturned);

        /*
        std::cout << "nFrame: " << nFrame 
                  << ", nFrameReturned: " << nFrameReturned 
                  << ", nVideoBytes: " << nVideoBytes << std::endl; 
        */

        if (!nFrame && nFrameReturned)
        {
            std::cout << dec.GetVideoInfo(); 
        }

        for (int i=0; i<nFrameReturned; ++i)
        {
            fpOut.write(reinterpret_cast<char*>(ppFrame[i]), dec.GetFrameSize()); 
        }
        nFrame += nFrameReturned; 
    } while (nVideoBytes); 

    std::cout << "Total frame decoded: " << nFrame << std::endl
              << "Saved in file: " << szOutFilePath << std::endl; 

    fpOut.close();

}