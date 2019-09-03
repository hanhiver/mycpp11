#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include "../common.hpp"
using namespace std;

class IntSequence 
{
private:
	int value;
public:
	IntSequence(int initValue) : value(initValue) {}
	int operator() () 
	{
		return ++ value;
	}
};

class FeboSeq
{
private:
	int n0;
	int n1;
public:
	FeboSeq()  
	{
		n0 = 0;
		n1 = 1;
	}
	int operator() () 
	{	
		int temp = n1;
		n1 = n0 + n1;
		n0 = temp;
		return n0;
	}
};

int main()
{
	list<int> coll;

	generate_n(back_inserter(coll), 9, IntSequence(1));
	print(coll, "Initialzied: ");

	generate(next(coll.begin()), prev(coll.end()), IntSequence(42));
	print(coll, "Regenerated: ");

	list<int> coll2;
	FeboSeq feb = FeboSeq();
	/*
	for (int i=0; i<10; ++i)
	{
		coll2.push_back(feb());
	}*/
	generate_n(back_inserter(coll2), 10, feb);
	print(coll2, "Feboseq: ");
}