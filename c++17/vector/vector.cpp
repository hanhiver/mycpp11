#include <iostream> 
#include <vector> 
#include <algorithm> 

int main()
{
    std::vector<int> v{1, 2, 3, 2, 5, 2, 6, 2, 4, 8};
    const auto new_end(std::remove(std::begin(v), std::end(v), 2));
    v.erase(new_end);

    for (auto& i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl; 

    const auto odd([](int i){ return i%2==0; });
    v.erase(std::remove_if(v.begin(), v.end(), odd), v.end());
    v.shrink_to_fit();

    for (auto& i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl; 
}
