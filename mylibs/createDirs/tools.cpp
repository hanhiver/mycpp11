#include "tools.hpp"

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
