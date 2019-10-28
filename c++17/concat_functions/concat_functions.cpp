#include <iostream> 
#include <functional> 

template <typename T, typename ... Ts> 
auto concat(T t, Ts ... ts)
{
    if constexpr(sizeof...(ts) > 0)
    {
        return [=](auto ...parameters)
        {
            return t(concat(ts...)(parameters...));
        };
    }
    else
    {
        return t; 
    }
}

int main()
{
    auto twice([](int i) 
                {
                    std::cout << "Call Twice. " << std::endl;  
                    return i*2; 
                }); 

    auto thrice([](int i) 
                {
                    std::cout << "Call Thrice. " << std::endl; 
                    return i*3; 
                });

    // The combined function should be:
    // (1). c = a + b => std::plus
    // (2). d = c * 3 => thrice
    // (3). e = d * 2 => twice
    auto combined(concat(twice, thrice, std::plus<int>{}));

    std::cout << combined(2, 3) << std::endl; 
}
