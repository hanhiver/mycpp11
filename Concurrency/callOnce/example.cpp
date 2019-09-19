#include <mutex>
#include <vector>
#include <iostream>

std::once_flag f; 

void call_once_func()
{
    std::cout << "I shall only be call once. " << std::endl;
}

void call_manytimes_func()
{
    std::call_once(f, call_once_func);
    std::cout << "I can be call many times. " << std::endl;
}

int main()
{
    call_manytimes_func();
    call_manytimes_func();
    call_manytimes_func();
}