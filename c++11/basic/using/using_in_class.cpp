#include <iostream> 
#include <string> 
#include <thread>

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

    void run()
    {
        std::thread t(Test::print, Object);
        t.join();
    }

private:
    mystr data; 
};
}

int main()
{
    dd::Test* a;
    a = new dd::Test {};
    a->run();
    //a->print();

    delete a; 
    return 0; 
}