#include <iostream>
#include <chrono>

#include "threads_pool.hpp"

void hello(int idx)
{
    std::cout << "#" << idx << ", " << std::this_thread::get_id() << std::endl; 
}

int main()
{
    thread_pool tpool(1);

    for (int i=0; i<12; ++i)
    {
        tpool.commit(hello, i);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    return EXIT_SUCCESS;
}
