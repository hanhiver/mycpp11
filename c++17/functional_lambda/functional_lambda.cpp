#include <iostream> 
#include <deque> 
#include <list> 
#include <vector> 
#include <functional> 

template <typename C> 
static auto consumer(C& container)
{
    return [&] (auto value)
    {
        container.push_back(value);
    };
}

template <typename C> 
static void print(const C& c)
{
    for (auto i : c)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl; 
}

int main()
{
    std::deque<int> d; 
    std::list<int> l; 
    std::vector<int> v; 

    const std::vector<std::function<void(int)>> consumers 
        { consumer(d), consumer(l), consumer(v)};
}