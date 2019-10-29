#include <iostream> 
#include <string> 
#include <string_view> 
#include <sstream> 
#include <algorithm> 
#include <cctype> 

using namespace std::literals; 

int main()
{
    std::string a {"a"};
    auto b ("b"s);

    std::string_view c {"c"};
    auto d ("d"sv);

    std::cout << a << ", " << b << std::endl; 
    std::cout << c << ", " << d << std::endl; 

    std::cout << a + b << std::endl; 
    std::cout << a + std::string{c} << std::endl; 

    std::ostringstream o; 
    o << a << " " << b << " " << c << " " << d; 
    auto con (o.str());
    std::cout << con << std::endl; 

    std::transform(std::begin(con), std::end(con), std::begin(con), ::toupper);
    std::cout << con << std::endl; 
}