#include <iostream> 
#include <string> 

#include "hello.h"
#include "world.h"

int hello()
{
    std::string name = "handong";
    std::cout << "Hello from lib. " << std::endl;
    world(name);
    return 0;
}
