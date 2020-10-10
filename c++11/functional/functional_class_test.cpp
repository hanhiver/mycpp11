#include <iostream> 
#include <functional> 

void sayhi()
{
    std::cout << "Hi" << std::endl;
}

class Timer
{
public:
    Timer();
    Timer(const Timer& timer);
    ~Timer();

    void hi();
    void set_name(std::string);
    void hello(std::string);
    
private:
    class TimerImpl;
    TimerImpl* impl;
};

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

void Timer::hi()
{
    std::cout << "Timer hi. " << std::endl; 
}

int main()
{
    Timer t;
    /* 
    t.hello("Trump");
    t.set_name("Biden");
    t.hello("Handong");
    */

    std::function<void()> Func;
    Func = sayhi;
    Func();

    Func = std::bind(&Timer::hi, t);
    Func(); 
    return 0;
}