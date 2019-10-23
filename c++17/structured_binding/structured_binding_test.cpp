#include <iostream> 
#include <map> 

std::pair<int, int> divide_remainder(int divident, int divisor)
{
    return std::make_pair(divident/divisor, divident%divisor);
}

int main()
{
    // C++11 code. 
    const auto result (divide_remainder(16, 3)); 
    std::cout << "16 / 3 is " << result.first 
              << " with a reminder " << result.second << std::endl; 
    
    // C++17 code.
    // Structured binding, auto detect and set the the type of fraction and remainder. 
    auto [fraction, remainder] = divide_remainder(16, 3);
    std::cout << "16 / 3 is " << fraction 
              << " with a reminder " << remainder << std::endl; 

    // c++17 code. 
    // Using structured binding to automatically print values in a map. 
    std::map<std::string, size_t> animal_population 
    {
        {"humans", 7000000000},
        {"chickens", 17863376000},
        {"camels", 24246291},
        {"sheep", 1086881528},
    };

    for (const auto& [species, count] : animal_population) 
    {
        std::cout << "There are " << count << " " << species
                  << " on this planet.\n";
    }

    return 0; 
}
