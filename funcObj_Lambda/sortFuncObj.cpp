#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

template <typename T>
class Sort
{
public:
	bool operator() (const T& a, const T& b) const
	{
		return a < b;
	}
};

int main()
{
	int a = 1; 
	int b = 2; 

	Sort<int> s = Sort<int>();

	cout << "a < b : " << bool(a < b) << endl;
	cout << "a < b : " << bool(s(a, b)) << endl;
	cout << "a < b : " << bool(Sort<int>()(a, b)) << endl;
}