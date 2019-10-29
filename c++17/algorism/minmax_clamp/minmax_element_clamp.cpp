#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iterator> 

static auto norm (int min, int max, int new_max)
{
    const double diff (max - min);
    return [=] (int val) 
        {
            return int((val - min) / diff * new_max);
        };
}

static auto clampval (int min, int max)
{
    return [=] (int val) -> int 
        {
            return std::clamp(val, min, max);
        };
}

int main()
{
    std::vector<int> v {0, 1000, 5, 250, 300, 800, 900, 321};
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>{std::cout, ", "});
    std::cout << std::endl; 

    const auto [min_it, max_it] (std::minmax_element(std::begin(v), std::end(v)));

    std::vector<int> v_norm; 
    v_norm.reserve(v.size());

    // Copy all the elements from v to v_normal and call norm funtion to do the normalization. 
    std::transform(std::begin(v), std::end(v), std::back_inserter(v_norm), 
                norm(*min_it, *max_it, 255));
    std::copy(std::begin(v_norm), std::end(v_norm), std::ostream_iterator<int>{std::cout, ", "});
    std::cout << std::endl; 

    // Call std::clamp to limit the number not exceed the min/max. 
    std::transform(std::begin(v), std::end(v), std::begin(v_norm), clampval(0, 255));
    std::copy(std::begin(v_norm), std::end(v_norm), std::ostream_iterator<int>{std::cout, ", "});
    std::cout << std::endl; 
}