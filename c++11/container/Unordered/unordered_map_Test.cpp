#include <unordered_map>
#include <numeric>
#include <iostream>
#include "../../common.hpp"
using namespace std;

void prepare_map(const unordered_map<std::string, int>& map_in, unordered_map<std::string, int>& map_out)
{
	unordered_map<std::string, int> mymap = {
		{"ten", 10}, 
		{"hundred", 100}, 
		{"thousand", 1000} 
	};
	
	map_out = map_in;
	map_out["ten"] = 10;
}

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

	std::cout << "Test map clone: " << std::endl;
	unordered_map<std::string, int> new_map;
	prepare_map(mymap, new_map);
	std::cout << "NEW MAP: " << std::endl;
	printMap(new_map);

	std::cout << "ORIG MAP: " << std::endl; 
	printMap(mymap);

	return 0;
}