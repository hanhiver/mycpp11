#include <iostream> 

void swap(long& a, long& b)
{
    long temp; 

    temp = a; 
    a = b; 
    b = temp;
}

int main()
{
    std::cout << "类型匹配的时候，引用可以直接操纵内部值：" << std::endl; 
    int a = 2;
    int b = 3; 
    std::cout << "Before, a = " << a << ", b = " << b << std::endl; 
    swap(a, b);
    std::cout << "After,  a = " << a << ", b = " << b << std::endl; 

    std::cout << "类型不匹配的时候，引用会生成临时变量在内部使用，外部值不发生变化：" << std::endl; 
    long x = 2;
    long y = 3; 
    std::cout << "Before, x = " << x << ", y = " << y << std::endl; 
    swap(x, y);
    std::cout << "After,  x = " << x << ", y = " << y << std::endl; 

    return 0; 
}