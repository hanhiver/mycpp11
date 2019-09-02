#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
using namespace std;

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
	std::array<int, 5> coll = {42, 377, 611, 21, 44};
	print(coll, "Initilized: ");

	auto coll2 = move(coll);
	print(coll2, "Moved (coll2): ");

	// Array promise that can access the data by old ctype. 
	printf("Third value is: %d\n", *(&coll2[0] + 2));

	// Array provide tuple interface. 
	typedef array<string, 5> FiveStrings;
	FiveStrings a = {"hello", "nico", "how", "are", "you"};
	cout << "Number of element: " << tuple_size<FiveStrings>::value << endl;
	cout << "The second element is: " << get<1>(a) << endl;
}