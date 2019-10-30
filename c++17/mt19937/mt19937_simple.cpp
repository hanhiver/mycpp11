#include <iostream> 
#include <random> 

int main()
{
    std::mt19937 mt_rand(time(0));
    
    for (unsigned i=0; i<10; ++i)
    {
        std::cout << mt_rand() << ", "; 
    }
    std::cout << std::endl; 
}