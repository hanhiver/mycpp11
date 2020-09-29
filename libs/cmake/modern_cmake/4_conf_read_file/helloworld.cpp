#include <iostream> 
#include "version.h"

int main()
{
    std::cout << "Hello! Cmake world! " << std::endl; 
    std::cout << "major: " << MY_VERSION_MAJOR << "\n"
              << "minor: " << MY_VERSION_MINOR << "\n"
              << "patch: " << MY_VERSION_PATCH << "\n"
              << std::endl; 
    
    return 0; 
}