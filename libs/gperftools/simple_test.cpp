#include <gperftools/profiler.h>
#include <stdlib.h> 

void f()
{
    int i;
    for (i=0; i<1024*1024; ++i)
    {
        char *p = (char *)malloc(120*1024*1024);
        free(p);
    }
}

void fun1()
{
    f();
}

void fun2()
{
    f();
}

int main()
{
    ProfilerStart("test.prof");
    fun1();
    fun2();
    ProfilerStop();

    return 0;
}