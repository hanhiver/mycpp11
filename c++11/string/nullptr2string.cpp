#include <iostream> 
#include <string> 

int main()
{
    //char* np = nullptr; 
    char* np1 = NULL;
    char* np2 = nullptr; 

    std::cout << "OK? " << (np1 == np2) << std::endl; 
    /*
    std::string str = np1; 
    std::cout << "str.empty(): " << str.empty(); 
    */
    std::string str2 = "123";
    std::cout << str2.size() << std::endl; 

    return 0; 
}