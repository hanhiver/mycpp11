#include <iostream> 
#include <chrono> 
#include "ThreadPool.h"

long LOOPS = 20000000;
int POOL_SIZE = 2;

int Hello(int idx)
{
    std::cout << "#" << idx << ", hello." << std::endl; 
    return idx; 
}

int BigLoop(int idx, long loops)
{
    long long big_num = 0;
    for (long i=0; i<loops; ++i)
    {
        big_num += loops * loops / (loops - 1); 
        if (long(i)%(LOOPS/10) == 0)
        {
            std::cout << "#"; 
        }
    }
    return idx; 
}

int main()
{
    ThreadPool tpool(POOL_SIZE);
    std::vector<std::future<int>> results;

    int tasks = 12;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<tasks; ++i)
    {
        results.emplace_back(tpool.enqueue(BigLoop, i, LOOPS/POOL_SIZE));
    }
    
    for (auto& item : results)
    {
        std::cout << item.get() << " ";
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double period = double(dur.count());

    std::cout << "\nRun Time: " << period/1000.0 << " ms. " << std::endl; 
    
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}