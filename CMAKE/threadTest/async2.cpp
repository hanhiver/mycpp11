#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
using namespace std;

int doSomething(char c)
{
    // random-number generator. 
    std::default_random_engine dre(c+1);
    std::uniform_int_distribution<int> id(10, 1000);

    // loop to print character after a random period of time. 
    for (int i=0; i<10; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }

    return c; 
}

int main()
{
    cout << "starting 2 operations asynchronously" << endl;

    // start two loops in background printing characters
    auto f1 = async([]{ doSomething('.'); });
    auto f2 = async([]{ doSomething('+'); });

    // if at least one of the background tasks is running. 
    if (f1.wait_for(chrono::seconds(0)) != future_status::ready || 
        f2.wait_for(chrono::seconds(0)) != future_status::ready)
    {
        while (f1.wait_for(chrono::seconds(0)) != future_status::ready &&
               f2.wait_for(chrono::seconds(0)) != future_status::ready)
        {
            this_thread::yield();
        }
    }
    cout.put('\n').flush();

    // Wait for all loops to be finished and process any exception.
    try
    {
        f1.get();
        f2.get();
    }
    catch(const std::exception& e)
    {
        std::cerr << "EXCEPTION:" << e.what() << '\n';
    }
    cout << "\nDone" << endl;
}