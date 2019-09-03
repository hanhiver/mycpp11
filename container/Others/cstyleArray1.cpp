#include <iterator>
#include <vector>
#include <iostream>
#include "../../common.hpp"

int main()
{
	int vals[] = {33, 67, -4, 13, 5, 2};
	print(vals);

	// use begin() and end() for ordinary C array.
	std::vector<int> v(std::begin(vals), std::end(vals));
	print(v);

	// use global begin() and end() for containers: 
	std::copy(std::begin(v), std::end(v), 
		      std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}