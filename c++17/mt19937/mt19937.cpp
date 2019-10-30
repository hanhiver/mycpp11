#include <iostream> 
#include <vector> 
#include <random> 
#include <algorithm> 
//#include <execution> 

static bool odd(int n)
{
    return n%2; 
}

int main()
{
    std::vector<int> d(5000000);

    std::mt19937 gen; 
    std::uniform_int_distribution<int> dis(0, 100000);
    auto rand_num ([=]() mutable 
        {
            return dis(gen);
        });

    /*
    std::generate(std::execution::par, std::begin(d), std::end(d), rand_num); 
    std::sort(std::execution::par, std::begin(d), std::end(d));
    std::reverse(std::execution::par, std::begin(d), std::end(d));
    auto odds(std::count_if(execution::par, std::begin(d), std::end(d), odd));
    */
    std::generate(std::begin(d), std::end(d), rand_num); 
    std::sort(std::begin(d), std::end(d));
    std::reverse(std::begin(d), std::end(d));
    auto odds(std::count_if(std::begin(d), std::end(d), odd));

    std::cout << (100.0 * odds / d.size()) 
              << "% of the numbers are odd. " << std::endl; 
}