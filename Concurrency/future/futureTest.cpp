#include <iostream>
#include <future> 
#include <string> 
using namespace std; 

int sayHello(std::string who)
{
    std::cout << "Hello from " << who << std::endl;
    return 0;
}

int main()
{
    std::future<int> s1 = std::async(sayHello, "Dady");
    std::future<int> s2 = std::async(sayHello, "Monmy");

    s1.get();
    s2.get();

    return 0;
}