#include <set>
#include <deque>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>
using namespace std;
using namespace std::placeholders;

template <typename T>
void print(T& list, string initStr)
{
	cout << initStr << "\t";
	for (const auto& elem : list)
	{
		cout << elem << "\t";
	}
	cout << endl;
}

int main()
{
	set<int, greater<int>> coll1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	deque<int> coll2;
	print(coll1, "Initialized: ");

	// transform all elem into coll2 by multiplying them with 10.
	transform(coll1.cbegin(), coll1.cend(), 
			  back_inserter(coll2), 
			  bind(multiplies<int>(), _1, 10));
	print(coll2, "Transformed: ");

	// replace value equal to 70 with 42. 
	replace_if(coll2.begin(), coll2.end(), 
			   bind(equal_to<int>(), _1, 70), 
			   42);
	print(coll2, "Replaced:    ");

	// remove all elements with values between 50 and 80.
	coll2.erase(remove_if(coll2.begin(), coll2.end(), 
		        bind(logical_and<bool>(), 
		        	 bind(greater_equal<int>(), _1, 50), 
		        	 bind(less_equal<int>(), _1, 80))), 
				coll2.end());
	print(coll2, "Removed:     ");

}