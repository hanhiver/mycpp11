#include <iostream>
#include <string>
#include "common.hpp"
using namespace std; 

int main()
{
	static string h = "hello";

	cout << boolalpha << h.compare("hello") << endl;
	cout << boolalpha << h.compare("hellO") << endl;
}