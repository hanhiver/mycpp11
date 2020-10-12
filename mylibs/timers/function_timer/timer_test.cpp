#include <iostream>
#include <string> 
#include <thread> 
#include <chrono>
#include <functional>
#include <atomic> 
#include "timer.hpp"
//#include "cpptime.h"

//void test(CppTime::timer_id)
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
	void shutdown();

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
	//CppTime::Timer timer; 
	//void real_hello(CppTime::timer_id);
	void real_hello();
	//bool loop; 
	std::atomic<bool> loop;
};

Greeting::Greeting()
{
	impl = new GreetingImpl;
	impl->loop = true; 
}

Greeting::~Greeting()
{
	delete impl; 
}

void Greeting::hello()
{
	std::cout << "Greeting::hello" << std::endl; 
	impl->loop = true; 
	impl->real_hello();
}

void Greeting::shutdown()
{
	impl->loop = false; 
	impl->timer.stop_timer();
}

//void Greeting::GreetingImpl::real_hello(CppTime::timer_id)
void Greeting::GreetingImpl::real_hello()
{
	std::cout << "Greeting::GreeetingImpl::real_hello" << std::endl; 
	//timer.start_once(100, test);
	if (loop)
	{
		timer.start_once(100, std::bind(&Greeting::GreetingImpl::real_hello, *this));
		//timer.add(std::chrono::milliseconds(100), test);
		//timer.add(std::chrono::milliseconds(100), std::bind(&Greeting::GreetingImpl::real_hello, *this, std::placeholders::_1));
	}
}

int main(int argc, char* argv[])
{
	Greeting::Get().hello();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "SHUTDOWN" << std::endl; 
	Greeting::Get().shutdown();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "DONE! " << std::endl; 

	return 0;
}
