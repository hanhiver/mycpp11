#include <iostream> 
#include <boost/coroutine2/all.hpp>
#include <boost/coroutine2/detail/push_coroutine.hpp>
#include <boost/coroutine2/detail/pull_coroutine.hpp> 

// Solution 1. 
void foo1(boost::coroutines2::coroutine<int>::pull_type& sink)
{
    using coiter = boost::coroutines2::coroutine<int>::pull_type::iterator;

    for (coiter start=begin(sink); start!=end(sink); ++start)
    {
        std::cout << "#1 Retrive " << *start << "\n";
    }
}

// Solution 2. 
void foo2(boost::coroutines2::coroutine<int>::pull_type& sink)
{
    for (auto val : sink)
    {
        std::cout << "#2 Retrive " << val << "\n"; 
    }
}

// Solution 3. 
void foo3(boost::coroutines2::coroutine<int>::pull_type& sink)
{
    for (int i=0; i<3; i++)
    {
        std::cout << "#3 Retrive " << sink.get() << "\n"; 
        sink(); 
    }
}

int main()
{
    boost::coroutines2::coroutine<int>::push_type source1(foo1); 
    for (int i=0; i<3; i++)
    {
        source1(i);
    }

    std::cout << std::endl; 

    boost::coroutines2::coroutine<int>::push_type source2(foo2); 
    for (int i=0; i<3; i++)
    {
        source2(i);
    }

    std::cout << std::endl; 

    boost::coroutines2::coroutine<int>::push_type source3(foo3); 
    for (int i=0; i<3; i++)
    {
        source3(i);
    }

    return 0; 
}