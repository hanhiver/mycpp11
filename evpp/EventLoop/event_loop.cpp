#include <iostream> 
#include <thread> 
#include <functional>
#include <chrono>
#include <evpp/event_loop.h>

void hello()
{
    std::cout << "Hello from evpp/event_loop! " << std::endl; 
}


int main()
{
    evpp::EventLoop m_loop; 
    //m_loop.Run();
    m_loop.RunInLoop(hello);
    m_loop.Run();

    return 0;
}