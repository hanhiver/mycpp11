#include <iostream>
#include <string>
#include "common.hpp"
using namespace std; 
#define RH_ETCD_KEY_JOB                       RH_ETCD_KEY_REDHARE_VER_PRE "/job"

int main()
{
	static string h = "hello";

	cout << boolalpha << h.compare("hello") << endl;
	cout << boolalpha << h.compare("hellO") << endl;
	cout << RH_ETCD_KEY_JOB << endl;
}