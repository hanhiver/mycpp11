#include <iostream> 
#include <vector> 
#include <boost/algorithm/cxx11/all_of.hpp> 

using namespace boost::algorithm;

#define pbool(i)                 \
do {                             \
    std::cout << std::boolalpha  \
              << i << std::endl; \
} while(0) 

bool isOdd(int i)
{
    return i%2 == 1; 
}

bool lessThan10(int i)
{
    return i < 10; 
}

int main()
{
    std::vector<int> vect {0, 1, 2, 3, 14, 15};
    pbool(boost::algorithm::all_of(vect, isOdd));
    pbool(boost::algorithm::all_of(vect.begin(), vect.end(), lessThan10));
    pbool(boost::algorithm::all_of(vect.begin(), vect.begin()+3, lessThan10));

    pbool(boost::algorithm::all_of_equal(vect, 3)); 
    pbool(boost::algorithm::all_of_equal(vect.begin()+3, vect.begin()+4, 3)); 
}
