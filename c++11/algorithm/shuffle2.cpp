#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random> // For default_random_engine
#include "../common.hpp"
using namespace std; 

// Customized random operator. 
class MyRandom
{
public:
	ptrdiff_t operator() (ptrdiff_t max)
	{
		double tmp;
		tmp = static_cast<double>(rand()) 
				/ static_cast<double>(RAND_MAX);
		return static_cast<ptrdiff_t>(tmp * max);
	}
};

int main()
{
	vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	print(coll, "Initiallzed: ");

	random_shuffle(coll.begin(), coll.end());
	print(coll, "Shuffled:    ");

	sort(coll.begin(), coll.end());
	print(coll, "Sorted:      ");

	MyRandom rd;
	random_shuffle(coll.begin(), coll.end(), rd);
	print(coll, "Shuffled:    ");

}