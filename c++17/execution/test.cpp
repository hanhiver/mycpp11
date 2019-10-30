#include <iostream> 
#include <vector> 
#include <algorithm>
#include <execution> 

template <typename T> 
void print(T& t)
{
    for (auto& elem : t)
    {
        std::cout << elem << ", ";
    }
    std::cout << std::endl; 
}

int main()
{
    {
        std::vector<int> v {3, 1, 4, 1, 5, 9, 2, 6, 5, 1, 5, 7};
        print(v);

        std::sort(std::begin(v), std::end(v));
        print(v);
    }
    {
        std::vector<int> v {3, 1, 4, 1, 5, 9, 2, 6, 5, 1, 5, 7};

        std::sort(std::execution::par, std::begin(v), std::end(v));
        print(v);
    }


}