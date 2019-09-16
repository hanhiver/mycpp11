#include <iostream>

int main() 
{
	auto i = 42;
	float s[] = {1.0, 3.4, 5.9};
	auto j = &s;

	std::cout<<i<<std::endl;
	std::cout<<s[1]<<std::endl;

	return 0;
}

