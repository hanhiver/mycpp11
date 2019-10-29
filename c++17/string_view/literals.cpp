#include <iostream> 
#include <string> 
#include <string_view> 

template <typename T> 
static void print(T& t)
{
    std::cout << t << std::endl; 
}

int main()
{
    std::string a {"Hello! World!\n"};
    print(a); 

    std::string_view b { "I am a string_view. " }; 
    print(b); 

    using namespace std::literals; 
    auto c { "literals string_view. "sv}; 
    print(c); 
}