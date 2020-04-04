#include <iostream> 
#include <string> 

int main()
{
    //std::string str = "3.1415926";
    std::string str = "abc;";
    int num;
    try
    {
        num = std::stoi(str);
    }
    catch(const std::exception& e)
    {
        num = 0;
    }
    
    std::cout << num << std::endl; 
    
    return 0; 
}