#include <iostream> 
#include <vector> 
#include <algorithm>

template <typename ... Ts> 
auto sum(Ts ... ts)
{
    return (ts + ... + 0);
}

template <typename R, typename ... Ts> 
auto matches(const R& range, Ts ... ts)
{
    return (std::count(std::begin(range), std::end(range), ts) + ... );
}

int main()
{
    int the_sum { sum(1, 2, 3, 4, 5) };
    std::cout << the_sum << std::endl; 

    int no_para { sum() };
    std::cout << no_para << std::endl; 

    std::vector<int> v {1, 2, 3, 4, 5};
    std::cout << matches(v, 2, 5) << std::endl; 
    std::cout << matches(v, 100, 500) << std::endl; 
    std::cout << matches("abcdefg", 'x', 'y', 'z') << std::endl; 
    std::cout << matches("abcdefg", 'a', 'b', 'f') << std::endl; 

}