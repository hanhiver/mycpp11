#include <iostream> 
#include <variant> 
#include <list> 
#include <string> 
#include <algorithm> 

class cat 
{
    std::string name; 

public: 
    cat(std::string n) : name {n}
    {}

    void meow() const 
    {
        std::cout << name << " says Meow!\n"; 
    }
};

class dog 
{
    std::string name; 

public: 
    dog(std::string n) : name {n}
    {}

    void woof() const 
    {
        std::cout << name << " says Woof!\n"; 
    }
};

using animal = std::variant<dog, cat>; 

template <typename T>
bool is_type(const animal& a)
{
    return std::holds_alternative<T>(a);
}

struct animal_voice
{
    void operator()(const dog& d) const
    {
        d.woof(); 
    }

    void operator()(const cat& c) const 
    {
        c.meow(); 
    }
}; 

int main()
{
    std::list<animal> l {cat{"Tuba"}, dog{"Balou"}, cat{"Bobby"}};

    for (const animal& a : l)
    {
        switch (a.index())
        {
        case 0:
            std::get<dog>(a).woof();
            break;
        case 1:
            std::get<cat>(a).meow();
            break;  
        }
    }
    std::cout << "--------\n";
}