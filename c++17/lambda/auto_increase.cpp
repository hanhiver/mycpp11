#include <iostream> 

int main()
{
    auto counter( [count=0]() mutable
        {
            return ++count; 
        });

    for (int i=0; i<5; ++i)
    {
        std::cout << counter() << ", ";
    }
    std::cout << std::endl; 
}