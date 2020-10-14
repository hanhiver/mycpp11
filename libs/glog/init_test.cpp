#include <iostream>
#include <glog/logging.h>
 
int main(int argc, char* argv[]) 
{
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = false; // 是否将日志输出到stderr而非文件。
    FLAGS_alsologtostderr = false; //是否将日志输出到文件和stderr，如果：true，忽略FLAGS_stderrthreshold的限制，所有信息打印到终端。
    FLAGS_stderrthreshold = google::ERROR; //输出到stderr的限值，默认为2（ERROR），默认ERORR以下的信息(INFO、WARNING)不打印到终端。
 
    FLAGS_log_prefix = true; //设置日志前缀是否应该添加到每行输出。
    FLAGS_logbufsecs = 0; //设置可以缓冲日志的最大秒数，0指实时输出。
    FLAGS_max_log_size = 10; //设置最大日志文件大小（以MB为单位）。
    FLAGS_stop_logging_if_full_disk = true; //设置是否在磁盘已满时避免日志记录到磁盘。
 
    google::SetStderrLogging(google::GLOG_INFO); //大于指定级别的日志都输出到标准错误(包括自己)。注意：这个函数有时会失效，原因没有查到。
 
    google::SetLogDestination(google::GLOG_INFO, "log/prefix_"); //日志的输出目录和前缀。
    google::SetLogDestination(google::GLOG_WARNING, "log/prefix_");
    google::SetLogDestination(google::GLOG_ERROR, "log/prefix_");
    google::SetLogDestination(google::GLOG_FATAL, "log/prefix_");
 
    google::SetLogFilenameExtension(".zip"); //在日志文件名中级别后添加一个扩展名，适用于所有严重级别。
 
    LOG(INFO) << "INFO";
    LOG(WARNING) << "WARNING";
    LOG(ERROR) << "ERROR";
 
    google::ShutdownGoogleLogging();
    return 0;
}