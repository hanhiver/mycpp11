#include "tools.hpp"
#include <stdio.h>
#include "cpuid.h"


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
char cpuid[512] = {0};

bool get_cpu_id(std::string& cpu_id)
{
    int ax, bx, cx, dx;
    int level;
    int level_max = 3;
    int len = 0;
    int size; 

    for (level = 0; level < level_max; ++level)
    {
        __cpuid(level, ax, bx, cx, dx);

        if (0 == level)
        {
            size = sprintf(cpuid + len, "%08X", ax);
        }
        else if (1 == level)
        {
            size = sprintf(cpuid + len, "%08X-%08X-%08X", ax, cx, dx);
        }
        else if (2 == level)
        {
            size = sprintf(cpuid + len, "%08X-%08X-%08X", ax, bx, dx);
        }

        len += size;
        cpuid[len] = '_';
        ++len;
    }
    cpuid[len - 1] = 0;

    std::string(cpuid).swap(cpu_id);
    return true;
}
#endif
