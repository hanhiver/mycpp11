#include <iostream> 
#include <iterator> 
#include <numeric>

template <typename T> 
auto map(T fn)
{
    return [=] (auto reduce_fn) 
            {
                return [=] (auto accum, auto input)
                        {
                            return reduce_fn(accum, fn(input));
                        };
            };
}

template <typename T> 
auto filter(T predicate)
{
    return [=] (auto reduce_fn)
            {
                return [=] (auto accum, auto input)
                        {
                            if (predicate(input))
                            {
                                return reduce_fn(accum, input);
                            }
                            else
                            {
                                return accum; 
                            }
                        };
            };
}

int main()
{
    std::istream_iterator<int> it { std::cin };
    std::istream_iterator<int> end_it; 

    auto even ([](int i) 
                {
                    return i%2 == 0; 
                });

    auto twice([](int i)
                {
                    return i*2; 
                });
                
    auto copy_and_advance([](auto it, auto input)
                        {
                            *it = input; 
                            return ++it; 
                        });

    // std::accumulate is a folder function. 
    std::accumulate(it, end_it, 
                std::ostream_iterator<int> { std::cout, ", " }, 
                filter(even)(
                    map(twice)(
                        copy_and_advance
                    )
                ));

    std::cout << std::endl; 

}