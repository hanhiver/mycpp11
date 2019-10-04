#include <iostream>
#include <vector>
#include <algorithm> // for std::accumulate
#include <numeric>
#include <thread>
#include <functional> // for std::mem_fn
#include <chrono> // for system_clock::now()
#include <future> // for future

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);
    unsigned long const max_chunk_size = 25;

    if (length < max_chunk_size)
    {
        return std::accumulate(first, last, T());
    }
    else
    {
        Iterator mid_point = first; 
        std::advance(first, length/2);
        
        std::future<T> first_half_result = std::async(parallel_accumulate<Iterator, T>, first, mid_point, init);
        T second_half_result = parallel_accumulate<Iterator, T>(mid_point, last, T());
        return first_half_result.get() + second_half_result;
    }
}

int main()
{
    std::vector<long long> vect;
    for (int i=1; i<1000000; ++i)
    {
        vect.push_back(i);
    }

    std::cout << "Normal accumulate: " << std::endl;
    auto start = std::chrono::system_clock::now();
    long long res = std::accumulate(vect.cbegin(), vect.cend(), 0);
    auto end = std::chrono::system_clock::now();

    auto dur = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
    //double period = double(dur.count()*std::chrono::microseconds::period::num/std::chrono::microseconds::period::den);
    double period = double(dur.count());

    std::cout << "Result: " << res << " in " << period << " ms." << std::endl;

    std::cout << "\nParallel accumulate <" << std::thread::hardware_concurrency() << "> threads." << std::endl;
    start = std::chrono::system_clock::now();
    res = parallel_accumulate(vect.cbegin(), vect.cend(), 0);
    end = std::chrono::system_clock::now();

    dur = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
    //double period = double(dur.count()*std::chrono::microseconds::period::num/std::chrono::microseconds::period::den);
    period = double(dur.count());

    std::cout << "Result: " << res << " in " << period << " ms." << std::endl;
}