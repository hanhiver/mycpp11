#include <iostream> 
#include <string> 

int main()
{
    std::string str_raw = "1234-5678 9";
    std::cout << str_raw << std::endl; 

    size_t index = str_raw.find('-', 1);

    std::cout << index << std::endl;
    std::cout << str_raw.substr(0, index-1) << std::endl;
    std::cout << str_raw.substr(index+1) << std::endl;

    uint16_t v1 = atoi(str_raw.substr(0, index-1).c_str());
    uint16_t v2 = atoi(str_raw.substr(index+1).c_str());
    std::cout << "v1: " << v1 << " v2: " << v2 << std::endl;  

    std::string test_str = "Verification successful"; 
    std::cout << "Find test1: " << test_str.find("erification successful") << std::endl; 
    std::cout << "Find test2: " << test_str.find("Verification successful") << std::endl; 
    
    std::size_t idx1 = test_str.find("Verification successful");
    std::size_t idx2 = test_str.find("labdcd");

    std::cout << "Find result: " << std::boolalpha 
              << (std::string::npos != idx1) << std::endl;
    std::cout << "Find result: " << std::boolalpha 
              << (-1 != idx2) << std::endl;
    
    return 0;
}