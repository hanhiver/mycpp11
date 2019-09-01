#include <iostream>
#include <string>
#include <unordered_map>
using namespace std; 

int main()
{
	unordered_map<string, float> coll;

	coll["VAT1"] = 0.16;
	coll["VAT2"] = 0.07;
	coll["Pi"] = 3.1415;
	coll["an arbitrary number"] = 4983.223;
	coll["Null"] = 0;

	// change value
	coll["VAT1"] += 0.03;

	cout << coll["Pi"] * coll["VAT2"] << endl;

	unordered_map<string, float>::const_iterator pos;
	for (pos=coll.begin(); pos!=coll.end(); ++pos)
	{
		cout << pos->first << " - " << pos->second << endl;
	}
	cout << endl;

	for (auto cpos=coll.cbegin(); cpos!=coll.cend(); ++cpos)
	{
		cout << cpos->first << " - " << cpos->second << endl;
	}
	cout << endl;

	for (auto elem : coll)
	{
		cout << elem.first << " - " << elem.second << endl;
	}
}