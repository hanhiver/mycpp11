#include <iostream> 

//int const LENGTH = 10;
const int LENGTH = 10; 

int main()
{
    unsigned long* array = new unsigned long[LENGTH];

    for (int i=0; i<LENGTH; ++i)
    {
        array[i] = i*i; 
    }

    for (int i=0; i<LENGTH; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl; 

    delete[] array;
    return 0; 
}