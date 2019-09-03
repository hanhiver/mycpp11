#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "../common.hpp"

int main()
{
	std::vector<int> vect1 = {6, 2, 9, 4, 1, 3, 0};
	print(vect1, "Initialized: ");

	// If vector has been implemented as a normal pointer, 
	// The following line will report WRONG when compile it. 
	//std::sort(++vect1.begin(), vect1.end());
	//print(vect1, "Sorted:      ");

	// This is the best way in C++11 to ensure the compatibility. 
	std::sort(std::next(vect1.begin()), vect1.end());
	print(vect1, "Sorted:     ");

	// reverse the vector and copy it to a new vector. 
	std::vector<int> vect2;
	vect2.resize(vect1.size());
	
	std::copy(vect1.rbegin(), vect1.rend(), vect2.begin());
	print(vect2, "Copied:    ");

	auto pos = vect1.begin();
	std::advance(pos, 10);
	if (pos == vect1.end())
	{
		std::cout << *pos << std::endl;
	}
	else
	{
		std::cout << "OOPS!" << std::endl;
	}
}