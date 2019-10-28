#include <iostream> 
#include <vector> 
#include <map> 
#include <string> 
#include <tuple> 
#include <iterator> 
#include <algorithm> 

std::ostream& operator<<(std::ostream& os, const std::pair<int, std::string>& p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T> 
void print(T t)
{
    for (auto& elem : t)
    {
        std::cout << elem << ", ";
    }
    std::cout << std::endl; 
}

int main()
{
    std::vector<std::pair<int, std::string>> v {
        {1, "one"}, {2, "two"}, {3, "three"},
        {4, "four"}, {5, "five"}};
    
    std::map<int, std::string> m;

    // std::copy_n
    std::copy_n(std::begin(v), 3, std::inserter(m, std::begin(m)));
    print(m);
    
    m.clear();
    std::move(std::begin(v), std::end(v), std::inserter(m, std::begin(m)));
    print(m);
    print(v);
}