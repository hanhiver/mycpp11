#include <iostream>
#include <string> 
#include "timer.hpp"

void func1()
{
	std::cout << "打你怎地！" << std::endl;
}

void func2(std::string x)
{
	std::cout << "你打我呀，" << x << std::endl;
}

int main(int argc, char* argv[])
{
	Timer timer;

	// execute task every timer interval
	std::cout << "--- 开始周期定时器 ----" << std::endl;
	timer.start_timer(500, std::bind(func2, "傻X"));
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	timer.stop_timer();
	std::cout << "--- 停止周期定时器 ----" << std::endl;

    // execute task once after delay
	std::cout << "--- 开始一次性定时器 ----" << std::endl;
	timer.start_once(1000, func1);
	std::cout << "--- 停止一次性定时器 ----" << std::endl;

	getchar();
	return 0;
}
