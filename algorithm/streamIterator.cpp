#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	vector<string> coll;

	copy(istream_iterator<string>(cin), 
		 istream_iterator<string>(),
		 back_inserter(coll));

	cout << endl;

	sort(coll.begin(), coll.end());

	unique_copy(coll.cbegin(), coll.cend(), 
		        ostream_iterator<string>(cout, "\t"));

	cout << endl;
}