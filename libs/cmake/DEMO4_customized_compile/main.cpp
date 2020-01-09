#include <iostream> 

int main()
{
    #ifdef DOUBLE_HELLO
        std::cout << "Hello, hello! " << std::endl; 
    #else 
        std::cout << "Hello! " << std::endl; 
    #endif 

    return 0; 
}