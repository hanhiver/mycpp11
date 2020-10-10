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
    void callhi();
    void set_name(std::string);
    void hello(std::string);
    
private:
    class TimerImpl;
    TimerImpl* impl;
};

class Timer::TimerImpl
{
public:
    void greeting();
    void call_greeting();
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
    std::function<void()> mFunc; 
    mFunc = std::bind(&Timer::TimerImpl::greeting, *impl);
    mFunc();
}

void Timer::callhi()
{
    std::cout << "Timer callhi. " << std::endl; 
    std::function<void()> mFunc; 
    mFunc = std::bind(&Timer::TimerImpl::call_greeting, *impl);
    mFunc();
}

void Timer::TimerImpl::greeting()
{
    std::cout << "Greeting! " << std::endl; 
}

void Timer::TimerImpl::call_greeting()
{
    std::cout << "TimerImpl call_greeting" << std::endl; 
    std::function<void()> mFunc; 
    mFunc = std::bind(&Timer::TimerImpl::greeting, this);
    mFunc();
}

int main()
{
    Timer t;
    /* 
    t.hello("Trump");
    t.set_name("Biden");
    t.hello("Handong");
    */
    
    std::function<void()> Func1;
    Func1 = sayhi;
    Func1();
    
    std::cout << "=====" << std::endl;

    std::function<void()> Func2 = std::bind(&Timer::hi, &t);
    Func2(); 
    
    std::cout << "=====" << std::endl;

    t.callhi();

    std::cout << "=====" << std::endl;

    return 0;
}