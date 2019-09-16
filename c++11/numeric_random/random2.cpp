#include <random>
#include <iostream>
#include <sstream>

void printNumbers(std::default_random_engine& dre)
{
    for (int i=0; i<6; ++i)
    {
        std::cout << dre() << " ";
    }
    std::cout << std::endl;
}

int main()
{
    // create engine and generate numbers. 
    std::default_random_engine dre; 
    std::cout << "Print default random engine: " << std::endl; 
    printNumbers(dre);

    // create equal engine and generate numbers.
    std::default_random_engine dre2; 
    std::cout << "Print a new default random engine: " << std::endl; 
    printNumbers(dre2);

    // create engine with initial state specified by a seed. 
    std::default_random_engine dre3(42);
    std::cout << "Print a default random engine with seed 42: " << std::endl; 
    printNumbers(dre3);

    // save state of engine dre 
    std::stringstream engineState; 
    engineState << dre; 

    // generate numbers according to current state of dre. 
    std::cout << "Print a default random engine: " << std::endl; 
    printNumbers(dre);

    // restore saved state of engine dre and create numbers again. 
    engineState.clear(); // clear EOF bits. 
    engineState.seekg(0);
    engineState >> dre;
    dre.discard(2);

    std::cout << "Print a restored random engine: " << std::endl; 
    printNumbers(dre);
}