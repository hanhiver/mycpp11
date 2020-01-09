#include <string> 
#include "hello/hello.hpp"

int main()
{
    std::string msg {"CMake world! "};
    hello(msg);

    return 0;
}