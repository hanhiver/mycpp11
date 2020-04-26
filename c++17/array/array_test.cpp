#include <iostream> 
#include <array> 

int main()
{
    std::array<int, 3> arr {1, 2, 3};

    for (const auto& item : arr)
    {
        std::cout << item << ", ";
    }
    std::cout << std::endl;

    std::cout << "Max size: " << arr.max_size() << std::endl; 
    return 0;
}