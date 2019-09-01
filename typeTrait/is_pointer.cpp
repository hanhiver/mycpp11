#include <iostream>
#include <type_traits>

template <typename T>
void foo(const T& val)
{
	if (std::is_pointer<T>::value) 
	{
		std::cout << "foo() called for a pinter" << std::endl;
	}
	else
	{
		std::cout << "foo() called for a value" << std::endl;
	}
}

template<typename T>
void print_impl(const T& val, std::true_type)
{
	std::cout << "foo() called for pointer to " << *val << std::endl;
}

template<typename T>
void print_impl(const T& val, std::false_type)
{
	std::cout << "foo() called for value to " << val << std::endl;
}

template<typename T>
void print(const T& val)
{
	print_impl(val, std::is_pointer<T>());
}

int main()
{
	int a = 42;
	int* pa = &a; 

	foo(a);
	foo(pa);

	print(a);
	print(pa);

	return 0;
}