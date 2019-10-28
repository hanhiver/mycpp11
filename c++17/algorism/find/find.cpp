#include <iostream> 
#include <vector> 
#include <list> 
#include <algorithm> 
#include <string> 

struct city 
{
    std::string name; 
    unsigned population; 
};

bool operator==(const city& a, const city& b)
{
    return a.name == b.name && a.population == b.population;
}

std::ostream& operator<<(std::ostream& os, const city& city)
{
    return os << "{" << city.name << ", "
              << city.population << "}";
}

template <typename C> 
static auto opt_print(const C& container)
{
    return [end_it (std::end(container))] (const auto& item)
    {
        if (item != end_it)
        {
            std::cout << *item << '\n';
        }
        else
        {
            std::cout << "<end>\n";
        }
    };
}

int main()
{
    const std::vector<city> c {
        {"Aachen", 246000},
        {"Berlin", 3502000},
        {"Braunschweig", 251000},
        {"Cologne", 1060000} };

    auto print_city(opt_print(c));

    // Normal code, use the std::find to do the work. 
    {
        auto found_cologne( std::find(std::begin(c), std::end(c), 
                            city {"Cologne", 1060000}));
        print_city(found_cologne);
        std::cout << std::endl; 
    }

    // Only check the city name. 
    {
        auto found_cologne( std::find_if(std::begin(c), std::end(c), 
                            [](const auto& item)
                            {
                                return item.name == "Cologne";
                            }));
        print_city(found_cologne);
        std::cout << std::endl; 
    }

    // An elegant way is to build a predicate constructor. 
    {
        // population_more_than is a lambda func which input a unsigned i
        // and return another lambda func of the city.population > i. 
        auto population_more_than( [](unsigned i) 
                    {
                        return [=] (const city& item)
                            {
                                return item.population > i; 
                            }; 
                    }); 

        // Give find_if the population_more_than(2M). 
        auto found_lager(std::find_if(std::begin(c), std::end(c), 
                         population_more_than(2000000)));
        print_city(found_lager);
        std::cout << std::endl; 
    }

    const std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto print_int(opt_print(v)); 
    
    // binary search. The vector should be sorted. 
    bool contains_7 {std::binary_search(std::begin(v), std::end(v), 7)};
    std::cout << std::boolalpha << contains_7 << std::endl; 

    auto [lower_it, upper_it] (std::equal_range(std::begin(v), std::end(v), 7)); 
    print_int(lower_it);
    print_int(upper_it);

}