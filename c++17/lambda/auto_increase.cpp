#include <iostream> 

int main()
{
    // c++14：设置count的初始值只在c++14之后支持。
    // 这里count通过初始化的值进行类型判断。这里无法自定义特别的类型。
    auto counter( [count=0]() mutable
        {
            return ++count; 
        });

    for (int i=0; i<5; ++i)
    {
        std::cout << counter() << ", ";
    }
    std::cout << std::endl; 
}