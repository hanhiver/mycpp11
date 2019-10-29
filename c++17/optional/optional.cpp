#include <iostream> 
#include <optional> 

using oint = std::optional<int>; 

oint read_int()
{
    int i; 
    if (std::cin>>i) 
    {
        return {i}; 
    }
    return {}; 
}

oint operator+(oint a, oint b)
{
    if (!a || !b)
    {
        return {}; 
    }
    return { *a + *b }; 
}

oint operator+(oint a, int b)
{
    if (!a)
    {
        return {};
    }

    return { *a + b }; 
}

int main()
{
    std::cout << "Please enter 2 integers. \n"; 
    auto a {read_int()}; 
    auto b {read_int()}; 

    auto sum (a + b + 10);

    if (sum)
    {
        std::cout << *a << "+" << *b << "+10=" << *sum << std::endl;   
    }
    else
    {
        std::cout << "Sorry, input not correct. \n";
    }
}