#include <iostream>
#include <string> 
#include <thread> 
#include <chrono>
#include <functional>
#include "timer.hpp"

void test()
{
	std::cout << "Test OK. " << std::endl; 
}

class Greeting
{
public:
	static Greeting& Get()
	{
		static Greeting instance; 
		return instance; 
	}
	void hello();

private: 
	Greeting();
	~Greeting();

	class GreetingImpl;
	GreetingImpl* impl; 
};

class Greeting::GreetingImpl
{
public: 
	Timer timer; 
	void real_hello();
};

Greeting::Greeting()
{
	impl = new GreetingImpl;
}

Greeting::~Greeting()
{
	delete impl; 
}

void Greeting::hello()
{
	std::cout << "Greeting::hello" << std::endl; 
	impl->real_hello();
}

void Greeting::GreetingImpl::real_hello()
{
	std::cout << "Greeting::GreeetingImpl::real_hello" << std::endl; 
	//timer.start_once(100, test);
	timer.start_once(100, std::bind(&Greeting::GreetingImpl::real_hello, *this));
}

int main(int argc, char* argv[])
{
	Greeting::Get().hello();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "DONE! " << std::endl; 
	return 0;
}
