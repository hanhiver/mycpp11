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
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10, 1000);

    // loop to print character after a random period of time. 
    for (int i=0; i<10; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }

    return c; 
}

int func1()
{
    return doSomething('.');
}

int func2()
{
    return doSomething('+');
}

int main()
{
    std::cout << "Starting func1() in background"
              << " and func2() in freground: " << std::endl;
    
    // start func1() asynchronously. 
    std::future<int> result1(std::async(func1));
    
    // call func2() synchronously. 
    int result2 = func2();

    // print result(wait func1() to finish and add its result to resout2)
    int result = result1.get() + result2;

    std::cout << "\nResult of func1() + func2(): " << result << std::endl;
}
