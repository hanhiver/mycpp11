#include <unordered_map>
#include <numeric>
#include <iostream>
#include "../../common.hpp"
using namespace std;

int main()
{
	unordered_map<std::string, int> mymap = {
		{"one", 1}, 
		{"two", 2}, 
		{"three", 3} 
	};

	std::cout << mymap["one"] << std::endl;
	std::cout << mymap["four"] << std::endl;
	mymap["five"] += 1;
	
	printMap(mymap);
}