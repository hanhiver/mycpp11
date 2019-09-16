#include <iostream>
#include <type_traits>
#include <string>

template <typename T1, typename T2>
typename std::common_type<T1, T2>::type add (const T1& x, const T2& y)
{
	return x + y;
}

int main()
{
	int a = 10;
	long b = 15;
	auto c = add(10, 15);
	std::cout << "Sum: " << c << std::endl;
	
	std::string m = "hello! ";
	std::string n = "world! ";
	auto l = add(m, n);
	std::cout << "Sum: " << l << std::endl;
	
	return 0;	
}