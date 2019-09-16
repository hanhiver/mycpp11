#include <iostream>
#include <list>
#include <algorithm>
#include "../common.hpp"
using namespace std;

class Nth
{
private:
	int nth;
	int count;
public:
	Nth(int n) : nth(n), count(0)
	{}

	bool operator() (int)
	{
		return ++count == nth;
	}
};

int main()
{
	list<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	print(coll, "initilized: ");

	list<int>::iterator pos;
	
	// WRONG HERE:
	// Not only 3th but also the sixth element will be removed. 
	// Because the remove_if will keep a copy of the op inside its implementation. 
	pos = remove_if(coll.begin(), coll.end(), Nth(3));
	coll.erase(pos, coll.end());
	
	print(coll, "removed: ");
}