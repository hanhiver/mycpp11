#include <iostream> 
#include <thread>

class Test
{
public:
    Test() {}
    ~Test() {}

    void print()
    {
        std::cout << "Hello." << std::endl;
    }

    void run()
    {
        _t = new std::thread(&Test::print, this);
        _t->join();
    }

    std::thread* _t; 
    
};

int main()
{
    Test mytest = Test();
    
    std::thread t(&Test::print, &mytest);
    t.join();

    mytest.run();

    return 0; 
}