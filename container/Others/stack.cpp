#include <iostream>
#include <stack>
using namespace std;

int main()
{
	stack<int> stk; 
	for (int i : {1, 2, 3})
	{
		stk.push(i);
	}

	cout << "Top: " << stk.top() << endl;
	stk.pop();
	cout << "Top: " << stk.top() << endl;
	stk.pop();
	cout << "Top: " << stk.top() << endl;
}