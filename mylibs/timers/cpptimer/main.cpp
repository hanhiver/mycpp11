#include <iostream> 
#include "cpptime.h"

using namespace std::chrono;

int main()
{
    std::cout << "Main thread: " << std::this_thread::get_id() << std::endl; 

    // Start a task after 1 seconds. The main thread will sleep for 2 seconds. 
    CppTime::Timer t;
    t.add(seconds(1), [](CppTime::timer_id) 
    { 
        std::cout << "task thread: " << std::this_thread::get_id() << std::endl; 
    });
    std::this_thread::sleep_for(seconds(2));

    std::cout << "\nPeridically task: " << std::this_thread::get_id() << std::endl; 
    // A peridically task first execute after 2 seconds and after this every second. 
    // The event will be remvoe after 10 seconds. 
    auto id = t.add(seconds(2), [](CppTime::timer_id) 
    { 
        std::cout << "task thread: " << std::this_thread::get_id() << std::endl; 
    }, seconds(1));
    std::this_thread::sleep_for(seconds(10));
    t.remove(id);

    return 0; 
}