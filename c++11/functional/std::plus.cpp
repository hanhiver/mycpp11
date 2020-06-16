#include <iostream> 
#include <functional> 
#include <algorithm>

int main()
{
    int first [] = {1, 2, 3, 4, 5};
    int second [] = {10, 20, 30, 40, 50};
    int result [5];

    std::transform(first, first+5, second, result, std::plus<int>());

    //for (int i=0; i<5; i++)
    for (auto& item : result)
    {
        //std::cout << result[i] << ", ";
        std::cout << item << ", ";
    }
    std::cout << std::endl; 
    return 0;
}
