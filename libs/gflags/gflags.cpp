#include <iostream> 
#include <gflags/gflags.h> 

DEFINE_bool(isvip, false, "If Is VIP");
DEFINE_string(ip, "127.0.0.1", "connect ip");
DECLARE_int32(port);

static bool ValidatePort(const char* flagname, int32_t value)
{
    std::cout << "Validate port input. " << std::endl; 
    if (value>0 && value<32768)
    {
        return true; 
    }
    else
    {
        std::cout << "Invalide value for --" << flagname 
                  << " " << (int)value << std::endl; 
        return false; 
    }
}
DEFINE_int32(port, 80, "listen port");
static const bool port_dummy = google::RegisterFlagValidator(&FLAGS_port, &ValidatePort);

int main(int argc, char** argv)
{
    std::cout << "gflags test. " << std::endl; 

    google::SetVersionString("1.0.1");

    google::ParseCommandLineFlags(&argc, &argv, true);
    std::cout << "ip: " << FLAGS_ip << std::endl; 
    std::cout << "port: " << FLAGS_port << std::endl; 

    if (FLAGS_isvip)
    {
        std::cout << "isvip: " << FLAGS_isvip << std::endl; 
    }

    google::ShutDownCommandLineFlags();
    return 0; 
}