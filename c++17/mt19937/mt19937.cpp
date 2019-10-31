#include <iostream> 
#include <vector> 
#include <random> 
#include <algorithm> 
#include <execution> 
#include <chrono>

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

    std::cout << "=== Serial Version: ===" << std::endl; 
    {
        auto start = std::chrono::steady_clock::now(); 

        std::generate(std::execution::seq, std::begin(d), std::end(d), rand_num); 
        std::sort(std::execution::seq, std::begin(d), std::end(d));
        std::reverse(std::execution::seq, std::begin(d), std::end(d));
        auto odds(std::count_if(std::execution::seq, std::begin(d), std::end(d), odd));
        
        auto end = std::chrono::steady_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        double period = double(dur.count());

        std::cout << "TIME: " << period << "ms, "
                << (100.0 * odds / d.size()) 
                << "% of the numbers are odd. " << std::endl; 
    }

    std::cout << "=== Parallel Version: ===" << std::endl; 
    {
        auto start = std::chrono::steady_clock::now(); 

        std::generate(std::execution::par, std::begin(d), std::end(d), rand_num); 
        std::sort(std::execution::par, std::begin(d), std::end(d));
        std::reverse(std::execution::par, std::begin(d), std::end(d));
        auto odds(std::count_if(std::execution::par, std::begin(d), std::end(d), odd));
        
        auto end = std::chrono::steady_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        double period = double(dur.count());

        std::cout << "TIME: " << period << "ms, "
                << (100.0 * odds / d.size()) 
                << "% of the numbers are odd. " << std::endl; 
    }
}