#include <iostream> 
#include <string> 
#include <cstdlib> 

int main(int argc, char* argv[])
{
    char* res = std::getenv("PATH");
    std::string my_path; 
    my_path = std::move(std::string(res ? res : ""));
    std::cout << "My Path: " << my_path << std::endl;  
    
    my_path = "Hello! ";
    std::cout << "Hello: " << my_path << std::endl;  

    char* sss = ""; 
    std::string check { sss };
    std::cout << (check == "") << std::endl; 

    return 0;
}