#include <iostream>
#include <map>
#include "../../common.hpp"
using namespace std;

int main()
{
	map<int, string> mp = { {1, "one"}, {2, "two"}, {3, "three"} };
	printMap(mp, "Initial: ");
}