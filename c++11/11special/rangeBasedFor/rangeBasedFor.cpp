#include <iostream>

template <typename T>
void printElements (const T& coll)
{
	for (const auto& elem : coll)
	{
		std::cout << elem << "\t";
	}
	std::cout << std::endl;
}

int main()
{
	int a[] = {2, 3, 5, 7, 13, 17, 19};

	for (int i : a)
	{
		std::cout<<i<<"\t";
	}
	std::cout<<std::endl;

	for (auto& j : a)
	{
		j *= 2;
	}

	printElements(a);

	return 0;
}