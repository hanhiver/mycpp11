// 实现一个类似Haskell和Python中的zip函数的迭代器。
#include <iostream> 
#include <vector> 
#include <numeric> 

class zip_iterator
{
    using it_type = std::vector<double>::iterator;

    it_type it1; 
    it_type it2;

public:
    zip_iterator(it_type iterator1, it_type iterator2)
        : it1 {iterator1}, it2 {iterator2}
    {}

    zip_iterator& operator++()
    {
        ++ it1; 
        ++ it2; 
        return *this;
    }

    bool operator!=(const zip_iterator& o) const 
    {
        return (it1 != o.it1 && it2 != o.it2);
    }
    
    bool operator==(const zip_iterator& o) const 
    {
        return !operator!=(o);
    }

    std::pair<double, double> operator*() const 
    {
        return {*it1, *it2};
    }
};

// 迭代器实现完成，需要让迭代器兼容STL算法。所以我们需要对标准模板进行特化。
// 这里将迭代器定义为一个向前的迭代器，并且解引用后返回的是一对double值。
// 此处没有用difference_type，但是对于不同的编译器实现STL，可能需要。
namespace std 
{
template <>
struct iterator_traits<zip_iterator> 
{
    using iterator_category = std::forward_iterator_tag; 
    using value_type = std::pair<double, double>;
    using difference_type = long int; 
};
}

// 现在来定义范围类，begin和end函数都返回zip迭代器。
class zipper 
{
    using vec_type = std::vector<double>; 
    vec_type& vec1;
    vec_type& vec2;

public:
    zipper(vec_type& va, vec_type& vb) 
        : vec1 {va}, vec2 {vb}
    {}

    zip_iterator begin() const 
    {
        return {std::begin(vec1), std::begin(vec2)};
    }

    zip_iterator end() const 
    {
        return {std::end(vec1), std::end(vec2)};
    }
};

int main()
{
    std::vector<double> a {1.0, 2.0, 3.0};
    std::vector<double> b {4.0, 5.0, 6.0};

    // 生成zip类将两个vect连接起来。
    zipper zipped {a, b};

    const auto add_product([](double sum, const auto& p)
    {
        return sum + p.first * p.second;
    });

    const auto dot_product(std::accumulate(std::begin(zipped), std::end(zipped), 0.0, add_product));

    std::cout << dot_product << std::endl; 

    return 0;
}

