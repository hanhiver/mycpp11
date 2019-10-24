#include <iostream> 
#include <mutex> 

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
    // the variable a only exist inside the if area. 
    if (auto a(get_a_number()); a>0)
    {
        std::cout << "a < 0" << std::endl; 
    }
    else
    {
        std::cout << "a >= 0" << std::endl; 
    }

    // c++17 code. 
    // Another example is to use the lock_guard to protect some of the operation. 
    // The c++17 way is more safe and gracefull.
    std::mutex my_lock;  
    if (std::lock_guard<std::mutex> lg(my_lock); true)
    {
        std::cout << "Print this in a protected area. " << std::endl; 
    }

    return 0; 
}