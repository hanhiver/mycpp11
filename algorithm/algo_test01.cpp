#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> coll;
	coll.push_back(2);
	coll.push_back(5);
	coll.push_back(8);
	coll.push_back(4);
	coll.push_back(1);
	coll.push_back(6);
	coll.push_back(3);

	// find and print minimum and maximum elements.
	auto minpos = min_element(coll.cbegin(), coll.cend());
	auto maxpos = max_element(coll.cbegin(), coll.cend());
	cout << "Max: " << *maxpos << " Min: " << *minpos << endl;

	// sort all elements.
	sort(coll.begin(), coll.end());

	// find the first element with value 3.
	auto pos3 = find(coll.begin(), coll.end(), 3);

	// reverse the order of the found element with value 3 and all following elements. 
	reverse(pos3, coll.end());

	// print the elements.
	for (auto elem : coll)
	{
		cout << elem << " ";
	}
	cout << endl;

}