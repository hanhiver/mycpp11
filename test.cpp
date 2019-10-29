#include <iostream>
#include <string>
#include <thread> 
#include <memory>
#include <atomic> 

using namespace std; 

int main()
{
	static string h = "hello";

	cout << boolalpha << h.compare("hello") << endl;
	cout << boolalpha << h.compare("hellO") << endl;
	cout << std::thread::id() << endl;

	int a = 42; 
	shared_ptr<int> pa = make_shared<int>(a);
	cout << *pa << endl;
	// 判断平台是否提供一个无锁实现的shared_ptr()
	cout << boolalpha << atomic_is_lock_free(&pa) << endl;

	auto pp = std::make_pair(2, "hello");
	std::cout << pp.first << ", " << pp.second << std::endl; 

	auto [num, str] (std::make_pair(42, "world"));
	std::cout << num << ", " << str << std::endl; 
}