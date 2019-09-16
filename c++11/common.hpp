#include <iostream>
#include <string> 
using namespace std;

template <typename T>
void print(T& list, const string& initStr = "")
{
    cout << initStr;
    for (const auto& elem : list)
    {
        cout << elem << "\t";
    }
    cout << endl;
}

template <typename T>
void printMap(const T& coll, const string& initStr = "")
{
	cout << initStr; 
	for (const auto& elem : coll)
	{
		cout << '[' << elem.first 
		     << ',' << elem.second << "] ";
	}
	cout << endl;
}
