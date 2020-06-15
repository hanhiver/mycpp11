#include <iostream> 
#include <functional> 

std::function<int(int)> Func; 

// 普通函数。
int ordinaryFunc(int a)
{
    return a*a; 
}

// 匿名函数
auto lambdaFunc = [](int a)->int { return a*a; };

// 仿函数
class Functor
{
public: 
    int operator()(int a)
    {
        return a*a; 
    }
};

// 成员函数和静态函数
class MyClass
{
public: 
    int ClassMember(int a) { return a*a; }
    static int StaticMember(int a) { return a*a; }
};

int main()
{
    Func = ordinaryFunc;
    std::cout << "普通函数： " << Func(1) << std::endl; 

    Func = lambdaFunc;
    std::cout << "Lambda函数： " << Func(2) << std::endl; 
    
    Functor fnt; 
    Func = fnt; 
    std::cout << "仿函数： " << Func(3) << std::endl; 
    
    MyClass mcls; 
    Func = std::bind(&MyClass::ClassMember, mcls, std::placeholders::_1);
    std::cout << "成员函数： " << Func(4) << std::endl; 

    Func = MyClass::StaticMember;
    std::cout << "静态函数： " << Func(5) << std::endl; 

    return 0; 
}