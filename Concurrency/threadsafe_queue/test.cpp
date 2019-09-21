#include <iostream>
#include <thread> 

#include "threadsafe_queue.hpp"

using namespace std;

void insert_int(threadsafe_queue<int> th, int num)
{
    for (int i=0; i<num; ++i)
    {
        th.push(i);
        std::cout << "Push: " << i << std::endl;
    }
}

int main()
{
    threadsafe_queue<int> th; 

    std::thread t1(insert_int, th, 5);
    /*
    th.push(1);
    th.push(2);

    int a, b; 

    th.wait_and_pop(a);
    th.wait_and_pop(b);

    std::cout << a << " " << b << std::endl;
    */
    
    for (int i=0; i<5; ++i)
    {
        std::cout << "Try to get one. " << std::endl;
        int x;
        th.wait_and_pop(x);
        std::cout << x << " ";
    }
    std::cout << std::endl;

    t1.join();
    
    return 0;
}