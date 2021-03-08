#ifdef WIN32
#include <io.h>
#include <direct.h>
#include <regex>
#else // LINUX or others
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <boost/regex.hpp>
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>

#include "tools.hpp"

std::int64_t str_time_to_time_stamp(const std::string& time_str)
{
#ifdef WIN32
    std::regex date_reg("^[0-9]{4}-(((0?[13578]|(10|12))-(0?[1-9]|[1-2][0-9]|3[0-1]))|(0?2-(0?[1-9]|[1-2][0-9]))|((0?[469]|11)-(0?[1-9]|[1-2][0-9]|30)))$");
    if (std::regex_match(time_str, date_reg))
    {
        return -1;
    }
#else
    // 在gcc<4.9的环境中，std:regex是不完整不可用的。
    // 出于兼容性的需要，此处使用了boost的regex库。
    boost::regex date_reg("^[0-9]{4}-(((0?[13578]|(10|12))-(0?[1-9]|[1-2][0-9]|3[0-1]))|(0?2-(0?[1-9]|[1-2][0-9]))|((0?[469]|11)-(0?[1-9]|[1-2][0-9]|30)))$");
    if (!boost::regex_match(time_str, date_reg))
    {
        return -1;
    }
#endif
    std::tm tm = {};
    std::string time_format{ "%Y-%m-%d" };
    std::istringstream ss{ time_str };
    
    ss >> std::get_time(&tm, time_format.c_str());
    //strptime(time_str.c_str(), "%Y-%m-%d", &tm);
    
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto tmp = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
    return tmp.count();
}

std::string read_file(const std::string& filename)
{
    std::ifstream inputFile;
    inputFile.open(filename, std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return "";
    }
    std::ostringstream buf;
    char ch;
    while(buf && inputFile.get(ch))
    {
        buf.put(ch);
    }
    inputFile.close();
    return buf.str();
}

int save_file(const std::string& filename, const std::string& content)
{
    std::ofstream out_file;
    out_file.open(filename, std::ios::trunc);
    if (!out_file.is_open())
    {
        std::cerr << "Failed to create file: " << filename << std::endl;
        return -1;
    }
    out_file << content.c_str();
    out_file.close();
    return 0;
}

int32_t createDirs(const std::string& dir_path)
{
    // 构建逐级创建的目录
    std::stringstream temp_path;

    for(uint32_t i=0; i<dir_path.length(); ++i)
    {
        temp_path << dir_path[i];

        // 逐级判断每一层目录。
        if (dir_path[i] == '\\' || dir_path[i] == '/')
        {
            // 检测到每一级目录判断目录是否存在。
            if (ACCESS(temp_path.str().c_str(), 0) != 0)
            {
                // 如果不存在则创建。
                int32_t ret = MKDIR(temp_path.str().c_str());
                if (ret != 0)
                {
                    return ret;
                }
            }
        }
    }

    return 0;
}

#ifndef WIN32
bool get_cpu_id(std::string& cpu_id)
{
    cpu_id.clear();

    unsigned int s1 = 0;
    unsigned int s2 = 0;
    asm volatile
    (
        "movl $0x01, %%eax; \n\t"
        "xorl %%edx, %%edx; \n\t"
        "cpuid; \n\t"
        "movl %%edx, %0; \n\t"
        "movl %%eax, %1; \n\t"
        : "=m"(s1), "=m"(s2)
    );

    if (0 == s1 && 0 == s2)
    {
        return(false);
    }

    char cpu[32] = { 0 };
    snprintf(cpu, sizeof(cpu), "%08X%08X", htonl(s2), htonl(s1));
    std::string(cpu).swap(cpu_id);

    return(true);
}
#endif
