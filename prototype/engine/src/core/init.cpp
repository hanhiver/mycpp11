#include <iostream> 
#include <string> 
#include <gflags/gflags.h>
#include <glog/logging.h>

#include "init.hpp"
#include "params.hpp"

// Define the gflag options. 
DEFINE_bool(h, false, "Show help");
DECLARE_bool(help);
DECLARE_bool(helpshort);
DEFINE_string(conf, "", "The configuration file. ");

int GlobalInit(int* pargc, char*** pargv)
{
    // Print output to stderr
    FLAGS_alsologtostderr = 1; 

    // ::gflags::ParseCommandLineFlags(pargc, pargv, true)
    gflags::SetVersionString("ws_engine prototype v0.1 dhan. \n");
    gflags::SetUsageMessage("");
    gflags::ParseCommandLineNonHelpFlags(pargc, pargv, true);
    if (FLAGS_help || FLAGS_h) 
    {
        FLAGS_help = false; 
        FLAGS_helpshort = false; 
    }
    gflags::HandleCommandLineHelpFlags();

    // Google logging init. 
    ::google::InitGoogleLogging(*(pargv)[0]);
    // Provide a backtrace on segfault. 
    ::google::InstallFailureSignalHandler();

    // Parse the args.
    if (FLAGS_conf.size() == 0)
    {
        LOG(ERROR) << "Usage: " << *pargv[0] << " --conf config_file"; 
        return EXIT_FAILURE;
    }

    if (!Params::Get().ParaseParamsFile(FLAGS_conf))
    {
        LOG(FATAL) << "Failed to parse conf file: " << FLAGS_conf; 
        return EXIT_FAILURE;
    }
    
    return 0;
}