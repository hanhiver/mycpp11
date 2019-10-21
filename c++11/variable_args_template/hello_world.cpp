#include <iostream> 
#include <initializer_list>

// 自定义函数处理递归调用的最后一个元素
template <typename T> 
void printValue(const T& t)
{
    // Print the last element. 
    std::cout << t << std::endl; 
}

// 递归方式调用实现参数挨个处理。
template <typename T, typename... Args>
void printValue(const T& t, const Args&... args)
{
    std::cout << t << " ";
    printValue(args...);
}

// 自定义函数处理单个传入的元素
template <typename T> 
void printEachValue(const T& t)
{
    // Print the last element. 
    std::cout << t << " "; 
}

// 利用逗号表达式和初始化列表展开参数，这个不需要递归调用。
template <typename... Args> 
void checkValue(const Args&... args)
{
    std::initializer_list<int>{ (printEachValue(args), 0)... };
    std::cout << std::endl; 
}

// 利用传参数的方式展开参数包，不确保会按照调用顺序展开。
template <typename T> 
int printArg(const T& t)
{
    // Print the last element. 
    std::cout << t << " "; 
    return 0; 
}

template <typename... Args>
void printArgsProxy(const Args&... args)
{}

template <typename... Args>
void printArgs1(const Args&... args)
{
    printArgsProxy(printArg(args)...);
    std::cout << std::endl; 
}

int main()
{
    printValue("Hello", ",", "World", "!"); 
    checkValue("Hello", ",", "World", "!"); 
    printArgs1("Hello", ",", "World", "!");

    return 0;  
}