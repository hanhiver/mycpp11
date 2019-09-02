#include <iostream>
#include <string> 
using namespace std;

template <typename T>
void print(T& list, string initStr = "")
{
    cout << initStr;
    for (const auto& elem : list)
    {
        cout << elem << "\t";
    }
    cout << endl;
}

