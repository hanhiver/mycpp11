#include <iostream> 
#include <vector> 

template <typename T> 
class addable
{
    T val; 
public: 
    addable(T v) : val(v) {}
    
    // c++ code. 
    // This can only handle single type. If we would like to add a vector structure, how to do it? 
    template <typename U>
    T add11(U x) const 
    {
        return val + x; 
    }

    // c++17 code. 
    // To extend the class that can accept a vector parameter input. 
    template <typename U>
    T add17(U x) const 
    {
        if constexpr(std::is_same<T, std::vector<U>>::value)
        {
            auto copy(val);
            for (auto& n : copy)
            {
                n += x; 
            }
            return copy; 
        }
        else
        {
            return val + x; 
        }
    }
};



template <typename T> 
void print(std::vector<T> vect)
{
    for (auto& elem : vect)
    {
        std::cout << elem << " "; 
    }
    std::cout << std::endl; 
}

int main()
{
    addable<int> a = {2};
    std::cout << "a + 2 = " << a.add11(2) << std::endl; 

    std::cout << addable<int> {1}.add17(2) << std::endl; 
    std::cout << addable<float> {1.f}.add17(2) << std::endl; 
    std::cout << addable<std::string> {"aa"}.add17("bb") << std::endl; 
    
    std::vector<int> v{1, 2, 3};
    print(addable<std::vector<int>> {v}.add17(10));

    std::vector<std::string> sv{"a", "b", "c"};
    print(addable<std::vector<std::string>> {sv}.add17(std::string {"z"}));
}