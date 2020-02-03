#include <iostream> 
#include <boost/signals2.hpp>

void hello() { std::cout << "Hello. " << std::endl; }
void my() { std::cout << "my " << std::endl; }
void world() { std::cout << "world! " << std::endl; }

int main()
{
    boost::signals2::signal<void ()> sig; 

    boost::signals2::connection conn_my; 

    sig.connect(&hello);
    conn_my = sig.connect(&my);
    sig.connect(&world);

    sig();

    std::cout << std::endl; 
    conn_my.disconnect(); 
    sig(); 

    return EXIT_SUCCESS;
}