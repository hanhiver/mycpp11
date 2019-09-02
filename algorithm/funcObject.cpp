#include <list>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

template <typename T>
void print(T& list, string initStr)
{
	cout << initStr << " ";
	for (const auto& elem : list)
	{
		cout << elem << " ";
	}
	cout << endl;
}

class AddValue 
{
private:
	int theValue;

public:
	AddValue(int v) : theValue(v)
	{

	}

	// Reference of the elem will change the elem. 
	void operator() (int& elem) const 
	{
		elem += theValue;
	}
};

int main()
{
	list<int> coll;

	for (int i=1; i<=9; ++i)
	{
		coll.push_back(i);
	}
	print(coll, "Initialized: ");

	for_each(coll.begin(), coll.end(), AddValue(10));
	print(coll, "After adding 10: ");

	for_each(coll.begin(), coll.end(), AddValue(*coll.begin()));
	print(coll, "After adding first element: ");
}

