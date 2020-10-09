#include "timer.hpp"

class Timer::TimerImpl
{
public:
    std::string mName; 
};

Timer::Timer()
{
    impl = new TimerImpl; 
    impl->mName = "no-name";
}

Timer::Timer(const Timer& timer)
{
    impl->mName = timer.impl->mName;
}

Timer::~Timer()
{
    impl->mName = "";
}

void Timer::set_name(std::string in)
{
    impl->mName = in; 
}

void Timer::hello(std::string in)
{
    std::cout << in << " say Hello to " << impl->mName << std::endl;
}