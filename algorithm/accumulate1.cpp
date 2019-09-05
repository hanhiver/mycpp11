#include <iostream>
#include <vector>
#include <numeric>
#include "../common.hpp"
using namespace std;

int main()
{
	vector<int> coll = {1,2,3,4,5,6,7,8,9};

	cout << "sum init(0): " << accumulate(coll.cbegin(), coll.cend(), 0) << endl;
	cout << "sum init(10): " << accumulate(coll.cbegin(), coll.cend(), 10) << endl;
	cout << "sum multiple: " << accumulate(coll.cbegin(), coll.cend(), 1, multiplies<int>()) << endl;
}