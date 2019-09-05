#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random> // For default_random_engine
#include "../common.hpp"
using namespace std; 

int main()
{
	vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	print(coll, "Initiallzed: ");

	random_shuffle(coll.begin(), coll.end());
	print(coll, "Shuffled:    ");

	sort(coll.begin(), coll.end());
	print(coll, "Sorted:      ");

	// Use 9 as the seed of the default random engine. 
	default_random_engine dre{9};
	shuffle(coll.begin(), coll.end(), dre);
	print(coll, "Shuffled:    ");

}