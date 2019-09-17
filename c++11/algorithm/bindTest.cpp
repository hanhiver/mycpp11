#include <iostream> 
#include <functional>

using namespace std;

int my_add(int a, int b, int c)
{
    return a + b + c;
}

int main()
{
    int a = 1; 
    int b = 2;
    int c = 3;

    cout << "my_add():       " << my_add(a, b, c) << endl;

    auto my_add_1 = std::bind(&my_add, std::placeholders::_1, std::placeholders::_2, 10); 
    cout << "my_add_1():     " << my_add_1(a, b) << endl;

    auto my_add_2 = std::bind(&my_add, std::placeholders::_1, 10, 100); 
    cout << "my_add_2():     " << my_add_2(a) << endl;
}