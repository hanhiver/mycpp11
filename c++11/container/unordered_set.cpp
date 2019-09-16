#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main()
{
	unordered_multiset<string> cities {
		"braunschweig", "Hanover", "frankfurt", "New York", 
		"Chicago", "Toronto", "Paris", "frankfurt"
	};

	// print each element
	for (const auto& elem : cities)
	{
		cout << elem << " ";
	}
	cout << endl; 

	// insert additional values. 
	cities.insert( {"London", "Munich", "Hanover", "Braunschweig"} );

	// print each element.
	for (const auto& elem : cities) 
	{
		cout << elem << " ";
	}
	cout << endl;
}
