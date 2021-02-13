#include <iostream> 

#include "mymath.h"

int main(int argc, char const *argv[])
{
    double a = myadd(1.1, 1.1);
    int b = myadd(1, 1);
    std::cout << "1.1加上1.1等于" << a << std::endl;
    std::cout << "1加上1等于" << b << std::endl; 
    
    return 0;
}