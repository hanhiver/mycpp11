#include <iostream> 
#include <string> 

class Timer
{
public:
    Timer();
    Timer(const Timer& timer);
    ~Timer();

    void set_name(std::string);
    void hello(std::string);
    
private:
    class TimerImpl;
    TimerImpl* impl;
};
