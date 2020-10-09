#include <iostream> 
#include <string> 

#include "timer.hpp"

int main()
{
    Timer t; 
    t.hello("Trump");
    t.set_name("Biden");
    t.hello("Handong");

    return 0;
}