#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>

template <typename T>
void insert_sorted(std::vector<T> &v, const std::string item)
{
    const auto insert_pos (std::lower_bound(std::begin(v), std::end(v), item));
    v.insert(insert_pos, item);
}

int main()
{
    std::vector<std::string> v {"some", "random", "words",
                                "without", "order", "aaa",
                                "yyy"};
    
    //assert(std::is_sorted(v.begin(), v.end()));
    std::sort(v.begin(), v.end());
    assert(std::is_sorted(v.begin(), v.end()));

    insert_sorted(v, "foorbar");
    insert_sorted(v, "zzz");

    for (auto& i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl; 


}


