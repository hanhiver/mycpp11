#include <iostream> 
#include <string> 
#include "hello.hpp"
#include "myadd.hpp"

int main()
{
    std::string msg {"CMake world! "};
    hello(msg);

    std::cout << "ADD 1+2 = " << myadd(1, 2) << std::endl; 

    return 0;
}
