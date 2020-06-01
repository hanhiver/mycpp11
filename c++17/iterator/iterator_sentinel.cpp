// 应用哨兵模式终止迭代
#include <iostream> 

class cstring_iterator_sentinel {}; 

class cstring_iterator
{
    const char* s {nullptr};

public:
    explicit cstring_iterator(const char* str) : s {str}
    {}

    char operator*() const { return *s; }

    cstring_iterator& operator++() 
    {
        ++s;
        return *this;
    }

    bool operator!=(const cstring_iterator_sentinel) const 
    {
        return s != nullptr && *s != '\0'; 
    }
};

class cstring_range
{
    const char* s {nullptr};

public: 
    cstring_range(const char* str) : s {str}
    {}

    cstring_iterator begin() const 
    {
        return cstring_iterator {s};
    }

    cstring_iterator_sentinel end() const 
    {
        return {};
    }
};

int main()
{
    char *str = "Hello, iterator sentinel!\n";

    for (char c : cstring_range(str))
    {
        std::cout << c;
    }
    std::cout << std::endl; 
}