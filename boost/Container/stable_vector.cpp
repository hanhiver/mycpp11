#include <iostream> 
#include <boost/container/stable_vector.hpp>

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

int main()
{
    boost::container::stable_vector<int> vect {1, 3, 4, 6, 7, 8};
    PELEMS(vect);

    vect.push_back(9);
    vect.push_back(88);

    PELEMS(vect);
    return 0;
}