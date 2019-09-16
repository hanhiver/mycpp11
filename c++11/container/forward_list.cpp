#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
	// create forward-list container. 
	forward_list<long> coll = {2, 3, 5, 7, 11, 13, 17};

	// resize two times. 
	// - note: poor performance. 
	coll.resize(9);
	coll.resize(10, 99);

	// print element. 
	for (auto elem : coll)
	{
		cout << elem << " ";
	}
	cout << endl;
}