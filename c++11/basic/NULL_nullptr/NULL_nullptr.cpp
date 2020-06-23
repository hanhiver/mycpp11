#include <iostream> 

int main()
{
    std::cout << "NULL = nullptr? : " 
              << std::boolalpha << (NULL == nullptr)
              << std::endl; 
              
    return 0; 
}