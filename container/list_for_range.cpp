#include <iostream>
#include <list>

using namespace std;

int main()
{
	list<char> coll;

	for (char c='a'; c<='z'; ++c)
	{
		coll.push_back(c);
	}

	// Use the const& to avoid the copy operation. 
	for (const auto& elem : coll)
	{
		cout << elem << ' ';
	}
	cout << endl;

	while (! coll.empty())
	{
		cout << coll.front() << ' ';
		coll.pop_front();
	}
	cout << endl;
}