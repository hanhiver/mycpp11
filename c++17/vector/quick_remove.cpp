#include <iostream> 
#include <vector> 
#include <algorithm>

template <typename T>
void quick_remove_at(std::vector<T> &v, std::size_t idx)
{
    if (idx < v.size())
    {
        v[idx] = std::move(v.back());
        v.pop_back();
    }
}

template <typename T> 
void quick_remove_at(std::vector<T> &v, typename std::vector<T>::iterator it)
{
    if (it != std::end(v))
    {
        *it = std::move(v.back());
        v.pop_back();
    }
}

int main()
{
    std::vector<int> v {123, 456, 789, 100, 200};

    // quick remove the index 2 element. 
    quick_remove_at(v, 2);
    quick_remove_at(v, std::find(v.begin(), v.end(), 123));
     
    for (auto& i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl; 

}
