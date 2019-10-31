#include <iostream> 
#include <chrono> 
#include <thread> 

using namespace std::chrono_literals; 

int main()
{
    std::cout << "Going to sleep for 1 seconds and 200 milli seconds. " << std::endl; 

    std::this_thread::sleep_for(1s + 200ms);

    auto m = 10s; 
    auto n = std::chrono_literals::operator""s(10); 
    std::cout << "Done! " << std::endl; 
}