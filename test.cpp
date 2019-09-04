#include <iostream>
#include <vector>
#include "common.hpp"
using namespace std; 

int main()
{
	vector<int> vect; 
	vector<int> vect2 {1, 2, 3, 4, 5, 6};

	vect.push_back(2);
	vect.push_back(3);
	vect.push_back(4);

	print(vect);
	vect.clear();
	print(vect);
	vect = std::move(vect2);
	vect2.clear();
	print(vect);
	

}