#include <glog/logging.h>

int main(int argc,char* argv[])
{
    google::InitGoogleLogging(argv[0]); //初始化 glog
    google::ParseCommandLineFlags(&argc, &argv, true);
    LOG(INFO) << "Hello,GOOGLE!";
    VLOG(100) << "VLOG info 100";
    VLOG(50) << "VLOG info 50";
    VLOG(10) << "VLOG info 10";
    return 0; 
}
