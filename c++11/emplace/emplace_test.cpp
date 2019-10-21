#include <iostream> 
#include <vector> 

class Test
{
    int _value; 

public: 
    Test() = default; 

    Test(int value) : _value(value)
    {
        std::cout << "Default" << std::endl; 
    }

    Test(const Test& t)
    {
        std::cout << "Copy " << std::endl; 
        _value = t._value * 3; 
    }

    void operator=(const Test& t)
    {
        std::cout << "Operator = " << std::endl; 
        _value = t._value * 2; 
    }

    friend std::ostream& operator<<(std::ostream& s, const Test& t)
    {
        s << "Test: " << t._value; 
        return s; 
    }
     
};

int main()
{
    /*
    Test a = Test(10);
    Test b = Test();
    b = a;  

    std::cout << a << std::endl; 
    std::cout << b << std::endl; 
    */
    std::vector<Test> vect; 

    Test c = Test(1);
    Test d = Test(1);

    vect.push_back(c);
    vect.push_back(d);

    //vect.emplace_back(c);
    //vect.emplace_back(d);

    for (auto& elem : vect)
    {
        std::cout << elem << std::endl;  
    }

    return 0; 
}