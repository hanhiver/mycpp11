#include <iostream> 

int get_a_number()
{
    return 1; 
}

int main()
{
    // c++ code
    auto a = get_a_number();
    if (a > 0)
    {
        std::cout << "a < 0" << std::endl; 
    }
    else
    {
        std::cout << "a >= 0" << std::endl; 
    }
    
    // c++17 code. 
    if (auto a(get_a_number()); a>0)
    {
        std::cout << "a < 0" << std::endl; 
    }
    else
    {
        std::cout << "a >= 0" << std::endl; 
    }

    return 0; 
}