#include <list>
#include <algorithm>
#include <iostream>
#include <cstdlib> // for abs()
using namespace std; 

// predicate, which returns whether an integer is a prime number. 
bool isPrime(int number)
{
	// ignore negative sign
	number = abs(number);

	if (number == 0 or number == 1)
	{
		return false;
	}

	int divisor; 
	for (divisor = number/2; number%divisor != 0; -- divisor)
	{
		;
	}

	return divisor == 1;
}

int main()
{
	list<int> coll;

	for (int i=24; i<=30; ++i)
	{
		coll.push_back(i);
	}

	auto pos = find_if(coll.cbegin(), coll.cend(), isPrime);

	if (pos != coll.end())
	{
		cout << *pos << " is first prime number found. " << endl;
	}
	else
	{
		cout << "No prime number found. " << endl;
	}
}