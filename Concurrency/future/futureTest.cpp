#include <iostream>
#include <future> 
#include <string> 
using namespace std; 

int sayHello(std::string who)
{
    std::cout << "Hello from " << who << std::endl;
    return 0;
}

void sayByebye()
{
    std::cout << "Byebye. " << std::endl;
}

int main()
{
    std::future<int> s1 = std::async(sayHello, "Dady");
    std::future<int> s2 = std::async(sayHello, "Monmy");
    std::future<void> s3 = std::async(sayByebye);

    int a = s1.get();
    int b = s2.get();
    s3.get();

    return 0;
}