#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <iterator>
#include <set>
#include <algorithm>
using namespace std; 

template <typename T> 
void print(T& coll)
{
	for (const auto& elem : coll)
	{
		cout << elem << " ";
	}
	cout << endl;
}

int main()
{
	list<int> coll1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	// copy the elements of coll1 into coll2 by appending them. 
	vector<int> coll2;
	copy(coll1.cbegin(), coll1.cend(), back_inserter(coll2));
	print(coll2);

	// copy the elements of coll1 into coll3 by inserting them at the front. 
	deque<int> coll3;
	copy(coll1.cbegin(), coll1.cend(), front_inserter(coll3));
	print(coll3);

	// copy element of coll1 into coll4.
	set<int> coll4;
	copy(coll1.cbegin(), coll1.cend(), inserter(coll4, coll4.begin()));
	print(coll4);
}