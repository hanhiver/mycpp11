#include <iostream> 
#include <boost/signals2.hpp> 

struct Hello
{
    void operator()() const 
    {
        std::cout << "Hello! ";
    }
};

struct World
{
    void operator()() const 
    {
        std::cout << "World! " << std::endl;
    }
};

int main()
{
    boost::signals2::signal<void ()> sig; 

    Hello h;
    World w;  
    sig.connect(h);
    sig.connect(w);

    sig.connect(1, World()); 
    sig.connect(0, Hello());

    sig(); 
}