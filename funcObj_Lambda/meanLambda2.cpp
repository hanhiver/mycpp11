#include <iostream>
#include <list>
#include <algorithm>
#include "../common.hpp"
using namespace std;

int main()
{
	list<int> coll = {1, 2, 3, 4, 5, 6, 7, 8};
	print(coll, "Initilied: ");

	// remove third element.
	list<int>::iterator pos;
	int count = 0;
	pos = remove_if(coll.begin(), coll.end(), 
		            [count] (int) mutable 
		            {
		            	return ++count == 3;
		            });
	coll.erase(pos, coll.end());
	print(coll, "3rd removed: ");
}