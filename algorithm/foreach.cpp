#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
using namespace std;

void print(int elem)
{
	cout << elem << ' ';
}

int square(int elem)
{
	return elem * elem;
}

int main()
{
	vector<int> coll;
	list<int> coll2;

	for (int i=1; i<=9; ++i)
	{
		coll.push_back(i);
	}

	for_each(coll.cbegin(), coll.cend(), print);
	cout << endl;

	transform(coll.cbegin(), coll.cend(), back_inserter(coll2), square);

	for (auto& elem : coll2)
	{
		print(elem);
	}
	cout << endl;
}