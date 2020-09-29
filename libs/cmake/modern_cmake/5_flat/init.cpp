#include <iostream> 
#include <string> 
#include <gflags/gflags.h>
#include <glog/logging.h>

#include "init.hpp"
#include "params.hpp"

DEFINE_bool(h, false, "Show help");
DECLARE_bool(help);
DECLARE_bool(helpshort);
DEFINE_string(conf, "", "The configuration file. ");

int GlobalInit(int* pargc, char*** pargv)
{
    // 错误同步输出到stderr
    FLAGS_alsologtostderr = 1;

    gflags::SetVersionString("SDK online manager test v0.1 (handong) \n");
    gflags::SetUsageMessage("");
    gflags::ParseCommandLineFlags(pargc, pargv, true);
    if (FLAGS_help || FLAGS_h)
    {
        FLAGS_help = false; 
        FLAGS_helpshort = false; 
    }
    gflags::HandleCommandLineHelpFlags();

    ::google::InitGoogleLogging(*(pargv)[0]);
    ::google::InstallFailureSignalHandler();

    // 如果没有指定配置文件地址，报错退出。
    if (FLAGS_conf.size() == 0)
    {
        LOG(ERROR) << "Usage: " << *pargv[0] << " --conf config_file";
        return EXIT_FAILURE;
    }

    // 如果解析配置文件出错，报错退出。 
    if (!Params::Get().ParaseParamsFile(FLAGS_conf))
    {
        LOG(FATAL) << "Failed to parse config file: " << FLAGS_conf;
        return EXIT_FAILURE;
    }

    return 0; 
}