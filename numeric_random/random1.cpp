#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include "../common.hpp"

int main()
{
    // create default engine as source of randomness.
    std::default_random_engine dre; 

    // use engine to generate integral numbers between 10 and 20. 
    std::uniform_int_distribution<int> di(10, 20);
    for (int i=0; i<20; ++i)
    {
        std::cout << di(dre) << " ";
    }
    std::cout << std::endl;

    // use engine to generate floating-point number between 10.0 and 20.0
    std::uniform_real_distribution<double> dr(10, 20);
    for (int i=0; i<8; ++i)
    {
        std::cout << dr(dre) << " ";
    }
    std::cout << std::endl;

    // use engine to shuffle elements
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    print(v, "Initilized: ");

    std::shuffle(v.begin(), v.end(), dre);
    print(v, "Shuffled:   ");

    std::cout << std:: endl;
}