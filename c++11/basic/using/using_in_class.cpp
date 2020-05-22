#include <iostream> 
#include <string> 

//using mystr=std::string;

namespace dd
{
using mystr=std::string;
class Test
{

public:
    Test()
    {
        data = "hello!";
    }
    ~Test(){}

    void print()
    {
        std::cout << data << std::endl;
    }

private:
    mystr data; 
};
}

int main()
{
    dd::Test* a;
    a = new dd::Test {};
    a->print();

    delete a; 
    return 0; 
}