#include <iostream> 

class A 
{
public:
    int a; 
};

A getTemp()
{
    return A();
}

int main()
{
    // refa是a的别名，正常的左值引用。    
    int a = 10;
    int& refa = a; 

    // 将不具名的变量取了个别名。1是右值，a是右值引用。
    int&& b = 1; 
    int c = 1; 
    //int&& d = c; // 编译错误！
    // getTemp()返回的是右值。
    A&& d = getTemp();  

    //A& e = getTemp(); // 编译错误。
    const A& e = getTemp();
}