#include <iostream> 
#include "bind_host.hpp"

int main()
{
    bool ret = BindCheck("../test.key");
    if (true == ret)
    {
        std::cout << "Bind check SUCCESS! " << std::endl;
    }
    else
    {
        std::cout << "Bind check FAILED! " << std::endl;
    }
    
    return 0;
}