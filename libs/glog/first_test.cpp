#include <glog/logging.h>

int main(int argc,char* argv[])
{
    google::InitGoogleLogging(argv[0]); //初始化 glog
    google::LogToStderr();
    LOG(INFO) << "Hello,GOOGLE!";
    LOG(ERROR) << "ERROR info!";
}
