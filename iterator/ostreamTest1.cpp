#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
	ostream_iterator<int> intWriter(cout, "\n");

	*intWriter = 42;
	intWriter ++;
	*intWriter = 77;
	intWriter ++;
	*intWriter = -5;

	vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout));
	cout << endl;
	
	copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " < "));
	cout << endl;
}	