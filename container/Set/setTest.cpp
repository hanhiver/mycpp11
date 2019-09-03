#include <set>
#include <iostream>
#include "../../common.hpp"
using namespace std;

int main()
{
	set<double> c;

	c.insert(1);
	c.insert(2);
	c.insert(3);
	c.insert(4);
	c.insert(5);
	c.insert(6);

	print(c);

	cout << "lower_bound(3): " << *c.lower_bound(3) << endl;
	cout << "upper_bound(3): " << *c.upper_bound(3) << endl;
	cout << "equal_bound(3): " << *c.equal_range(3).first << " "
	 						   << *c.equal_range(3).second << endl;
	cout << endl;

	cout << "lower_bound(5): " << *c.lower_bound(5) << endl;
	cout << "upper_bound(5): " << *c.upper_bound(5) << endl;
	cout << "equal_bound(5): " << *c.equal_range(5).first << " "
	 						   << *c.equal_range(5).second << endl;
	cout << endl;

	if (c.insert(3.3).second)
	{
		cout << "3.3 inserted." << endl;
	}
	else
	{
		cout << "3.3 already existed. " << endl;
	}
}