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

void five_seconds()
{
    std::cout << "Sleep for 5 seconds..."; 
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << " Done! " << std::endl; 
}

int main()
{
    std::cout << "=== started ===" << std::endl;
    Timer timer; 
    timer.start_once(1000, test);
    timer.stop_timer();
    std::cout << "=== done ===" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0; 
}