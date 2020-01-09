#include <string> 
#include "hello.hpp"

int main()
{
    std::string msg {"CMake world! "};
    hello(msg);

    return 0;
}