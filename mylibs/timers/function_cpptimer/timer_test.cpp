#include <iostream>
#include <string> 
#include <thread> 
#include <chrono>
#include <functional>
#include <atomic> 

#include "cpptime.h"

void test(CppTime::timer_id)
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

	void hi(CppTime::timer_id id);
	void hello();
	void shutdown();
	//void real_hello(CppTime::timer_id id);

private: 
	Greeting();
	~Greeting();

	CppTime::Timer timer; 
	void real_hello(CppTime::timer_id id);
	//bool loop; 
	std::atomic<bool> loop;
};


Greeting::Greeting() : 
	loop(false)
{
}

Greeting::~Greeting()
{
}

void Greeting::hi(CppTime::timer_id id)
{
	std::cout << "Hi: " << id << std::endl;
}

void Greeting::hello()
{
	std::cout << "Greeting::hello" << std::endl; 
	loop = true; 
	real_hello(0);
}

void Greeting::shutdown()
{
	loop = false; 
}

void Greeting::real_hello(CppTime::timer_id id)
{
	std::cout << "Greeting::real_hello" << std::endl; 
	if (loop)
	{
		//timer.add(std::chrono::milliseconds(100), test);
		//timer.add(std::chrono::milliseconds(100), std::bind(&Greeting::hi, this, std::placeholders::_1));
		timer.add(std::chrono::milliseconds(100), std::bind(&Greeting::real_hello, this, std::placeholders::_1));
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
