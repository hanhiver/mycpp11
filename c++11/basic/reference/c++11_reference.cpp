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
    
    int a = 10;
    int& refa = a; 
}