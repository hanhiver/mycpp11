#include "tools.hpp"

// 测试函数，创建多级目录
int32_t main(int32_t argc, char *argv[])
{
    if (argc == 2)
    {
        return createDirs(argv[1]);
    }
    return 0;
}
