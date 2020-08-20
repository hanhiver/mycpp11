#include <iostream> 

class B
{
public:
    int b; 
};

B getTemp()
{
    return B();
}

int main()
{
    const int& a = 123; // 常量左值绑定右值，ok
    const int&& x = std::move(a); // 右值引用可以使用std::move转化
    const B& m = getTemp(); 

    std::cout << "Done." << x << std::endl;
    return 0;
}