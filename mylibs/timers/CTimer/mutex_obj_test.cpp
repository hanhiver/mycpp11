#include <iostream>
#include <tuple>
#include <mutex>
#include <thread> 

#include "mutex_obj.hpp"

int main()
{
    MutexObject< int > obj2(0);
    do 
    {
        MUTEXOBJECT_LOCK_GUARD(obj2);
        int & tmp = obj2;
        ++tmp;
    } while (false);

    MutexObject< std::tuple<std::string, int, double, std::pair<int, int> > > 
        obj(std::string("FlushHip"), 1, 0.5, std::make_pair(2, 3));
    do {
        MUTEXOBJECT_LOCK_GUARD(obj);
        std::get<0>(obj.Data()) = "Hip";
        std::get<3>(obj.Data()).first = 3;
    } while (false);

    int value = 0;
    
    std::thread th1([&](){
        for (int i=0; i<10000; ++i)
        {
            value += 1; 
        }
    });

    std::thread th2([&](){
        for (int i=0; i<10000; ++i)
        {
            value -= 1; 
        }
    });

    th1.join();
    th2.join();

    std::cout << "Value = " << value << std::endl; 

    return 0; 
}