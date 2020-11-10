#include <vector> 
#include <algorithm>
#include <fstream> 
#include <string> 

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <fcntl.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "config.pb.h"

/**
 * @brief 参数集合 \n
 * 提供对于指定格式的配置文件读取然后生成参数供程序各个部分获取的类型
 */
class Params
{
public: 
    /** 
     * @brief 获取参数单例类型入口
     *
     * @return 返回单例类型参数
     */
    static Params& Get()
    {
        static Params instance; 
        return instance; 
    }

    /** 
     * @brief 从指定的配置文件中读取参数
     * @param filepath  指定的配置文件
     *
     * @return 返回是否成功读取配置文件。
     */
    bool ParaseParamsFile(std::string filepath);

    /** 
     * @brief 获取KeyInfo的读取入口
     *
     * @return 返回KeyInfo的配置读取入口
     */
    inline static const bind_host::KeyInfo& GetKeyInfo()
    {
        return mParams.key_info();
    }
    
    /** 
     * @brief 获取KeyInfo的读取入口
     *
     * @return 返回KeyInfo的配置读取入口
     */
    inline static const bind_host::InternalDebugOptions& GetInternalDebugOptions()
    {
        return mParams.internal_debug_options();
    }

    /** 
     * @brief 打印出读取到的配置信息
     *
     */
    void PrintParams();

    /** 
     * @brief 输出读取到的配置信息的字符串
     *
     * @retval 配置文件信息字符串
     */
    std::string ParamsString();

private: 
    Params() {}
    static bind_host::HostKey mParams; 
};
