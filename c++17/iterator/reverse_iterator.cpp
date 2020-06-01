#include <iostream> 
#include <list> 
#include <iterator> 

int main()
{
    std::list<int> l {1, 2, 3, 4, 5};

    // 正常的STL容器都提供了反向迭代器可以直接使用。
    std::copy(l.rbegin(), l.rend(), 
        std::ostream_iterator<int>{std::cout, ", "});
    std::cout << std::endl; 

    // C++17: 如果容器不支持反向迭代器，就需要双向迭代器来帮忙。
    // 可以使用工厂函数std::make_reverse_iterator创建双向迭代器。
    std::copy(std::make_reverse_iterator(std::end(l)), 
              std::make_reverse_iterator(std::begin(l)), 
              std::ostream_iterator<int>{std::cout, ", "});
    std::cout << std::endl; 

    return 0; 
}