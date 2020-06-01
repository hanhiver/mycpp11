// 使用std::function来扮演一个Lambda表达式多态包装器
#include <iostream> 
#include <deque> 
#include <list> 
#include <vector>
#include <functional> 

template <typename C>
static auto consumer(C& container)
{
    return [&](auto value)
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
        { consumer(d), consumer(l), consumer(v) };
    
    for (size_t i{0}; i<10; ++i)
    {
        // 这里为什么要用右值引用？ 需要思考。
        // 如下只用引用的话也可以工作。
        // for (auto&& item : consumers)
        for (auto&& item : consumers)
        {
            item(i);
        }
    }

    auto solo = consumer(d); 
    solo(100); 

    print(d);
    print(l);
    print(v);

    return 0;
}