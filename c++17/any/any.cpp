#include <iostream> 
#include <iomanip> 
#include <list> 
#include <vector> 
#include <any> 
#include <iterator> 

void print_anything(const std::any& a)
{
    if (!a.has_value())
    {
        std::cout << "[nothing]" << std::endl; 
    }
    else if (a.type() == typeid(std::string))
    {
        std::cout << "[string]: "
                  << std::quoted(std::any_cast<const std::string&>(a)) << std::endl; 
    }
    else if (a.type() == typeid(int))
    {
        std::cout << "[int]: "
                  << std::any_cast<int>(a) << std::endl; 
    }
    else if (a.type() == typeid(std::list<int>))
    {
        const auto& l (std::any_cast<const std::list<int>&>(a)); 

        std::cout << "[list]: "; 
        std::copy(std::begin(l), std::end(l), 
                  std::ostream_iterator<int>{std::cout, ", "});
        std::cout << std::endl; 
    }
    else
    {
        std::cout << "Cannot handle this item. " << std::endl; 
    }
}

int main()
{
    using namespace std::literals; 
    print_anything({});
    print_anything("abc"s);
    print_anything(123);
    print_anything(std::list<int>{1, 2, 3});
    print_anything(std::any(std::in_place_type_t<std::list<int>>{}, {1, 2, 3}));
    print_anything(std::vector<int>{3, 4, 5, 6, 7, 8}); 
}