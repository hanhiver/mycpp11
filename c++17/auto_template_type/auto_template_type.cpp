#include <iostream> 

template <typename T>
struct sum
{
    T value;

    template <typename ... Ts> 
    sum(Ts&& ... values) -> sum<std::common_type_t<Ts...>> : value {(values + ...)}
    {}

    void print()
    {
        std::cout << "Value: " << value << std::endl; 
    }
};

int main()
{
    sum s {1, 2, 3};
    std::cout << s.print() << std::endl; 
}
