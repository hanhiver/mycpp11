#include <iostream> 
#include <string>
#include "ThreadPool.h"

void hello(int i)
{
    std::cout << "#" << i << '\n';    
}

class Test
{
public: 
    Test(int thnum):tpool(thnum)
    {
        //ThreadPool tpool(thnum);
    }

    ThreadPool tpool; 
};

int main()
{
    Test t(4);

    for (int i=0; i<20; i++)
    {
        t.tpool.enqueue([&, i](){
            std::cout << "#" << i << '\n';
        });
    }

    return 0; 
}