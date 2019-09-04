#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MeanValue
{
private:
	long num; 
	long sum; 
public:
	MeanValue() : num(0), sum(0)
	{}

	void operator() (int elem)
	{
		++ num;
		sum += elem;
		cout << "handle: " << elem << "\t";
	}

	double value()
	{
		cout << "num: " << num << " sum: " << sum << endl;
		return static_cast<double>(sum) / static_cast<double>(num);
	}
};

int main()
{
	vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8};

	//MeanValue mv = for_each(coll.begin(), coll.end(), MeanValue());
	//cout << "Mean value: " << mv.value() << endl;

	MeanValue mv2 = MeanValue(); 
	mv2 = for_each(coll.begin(), coll.end(), mv2);
	cout << "Mean value: " << mv2.value() << endl;
}