#include <iostream> 

using namespace std; 

class A
{
public: 
    A():m_ptr(new int(0))
    {
        cout << "construct" << endl;
    }
    
    A(const A& a):m_ptr(new int(*a.m_ptr))
    {
        cout << "copy construct" << endl; 
    }

    A(A&& a):m_ptr(a.m_ptr)
    {
        a.m_ptr = nullptr;
        cout << "move construct" << endl; 
    }

    ~A()
    {
        delete m_ptr;
    }
private: 
    int* m_ptr; 
};

A GetA()
{
    return A();
}

int main()
{
    A a = GetA();
    return 0;
}