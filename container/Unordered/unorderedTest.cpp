#include <unordered_set>
#include <numeric>
#include <iostream>
#include "../../common.hpp"
using namespace std;

int main()
{
	unordered_set<int> coll = {1, 2, 3, 5, 7, 11, 13, 17, 19, 77};
	print(coll, "Initilized: ");

	// Insert some elements. 
	coll.insert({-7, 17, 33, -11, 17, 19, 1, 13});
	print(coll, "After insert: ");

	// remove element with specific value. 
	coll.erase(33);

	// insert sum of all existing value. 
	coll.insert(accumulate(coll.begin(), coll.end(), 0));
	print(coll);


	// remove all negative values. 
	unordered_set<int>::iterator pos;
	for (pos=coll.begin(); pos!=coll.end(); )
	{
		if (*pos < 0)
		{
			pos = coll.erase(pos);
		}
		else
		{
			++pos;
		}
	}

	print(coll);
}