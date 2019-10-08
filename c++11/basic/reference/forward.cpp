#include <iostream> 

void processValue(int& a)
{
    std::cout << "lvalue" << std::endl; 
}

void processValue(int&& a)
{
    std::cout << "rvalue" << std::endl; 
}

template <typename T> 
void forwardValue(T&& val)
{
    processValue(std::forward<T>(val));
}

int main()
{
    int i = 0;
    forwardValue(i); // 传入左值
    forwardValue(0); // 传入右值
}