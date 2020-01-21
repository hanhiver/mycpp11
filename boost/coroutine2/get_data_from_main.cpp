#include <iostream> 
#include <string> 
#include <boost/coroutine2/all.hpp>

void foo(boost::coroutines2::coroutine<std::string>::pull_type& sink)
{
    std::cout << "1. get " << sink.get() << " from main(). \n";
    sink();
    std::cout << "2. get " << sink.get() << " from main(). \n";
    sink();
}

int main()
{
    std::string str1("hello");
    std::string str2("world");

    boost::coroutines2::coroutine<std::string>::push_type source(foo);
    
    std::cout << "1. pass " << str1 << " to foo()\n";
    source(str1); 
    std::cout << "2. pass " << str2 << " to foo()\n";
    source(str2); 

    std::cout << "3. Done. " << std::endl; 
    return 0; 
}