#include <iostream>
#include <future> 

void helloThread()
{
    std::cout << "Hello from thread. " << std::endl;
}

int main()
{
    std::packaged_task<void()> t1(helloThread);
    t1();

    return 0;
}