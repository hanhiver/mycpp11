#include <iostream>
#include <algorithm>
#include <vector>

using namespace std; 

int main()
{
	int a = 42; 
	int b = 43;
	cout<<"min(a, b): "<<min(a, b)<<endl;

	vector<int> vect { 3, 1, 4, 1, 5, 9, 2, 6 };
	//cout<<"max(&vect): "<<max(vect)<<endl;

	return 0;
}
