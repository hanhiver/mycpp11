#include <iostream> 
#include <boost/coroutine2/all.hpp> 

typedef boost::coroutines2::coroutine<int> coro_t; 

void foo(coro_t::push_type& sink)
{
    int first = 1, second = 1; 
    sink(first);
    sink(second);
    
    for(int i=0; i<8; i++)
    {
        int third = first + second; 
        first = second; 
        second = third; 
        sink(third);
    }
}

int main()
{
    coro_t::pull_type source(foo);

    for (auto i : source)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl; 
    return 0; 
}