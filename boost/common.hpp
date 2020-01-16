#include <iostream> 

#define PELEMS(container)           \
do                                  \
{                                   \
    for (auto& item : container)    \
    {                               \
        std::cout << item           \
                  << ", ";          \
    }                               \
    std::cout << std::endl;         \
} while(0)
