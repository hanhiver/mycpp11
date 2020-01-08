#include <iostream> 
#include <vector> 
#include <sstream> 
#include <fstream> 

int main()
{
    std::vector<std::string> s_vect {"This ", "is ", "a ", "good ", "example. \n", 
                                     "What ", "is ", "your ", "throught? ", "\n" }; 
    
    std::stringstream ss; 
    for (auto item : s_vect)
    {
        ss << item << '\n'; 
    }

    std::cout << ss.str() << std::endl; 

    return EXIT_SUCCESS; 
}