#include <iostream>
#include <vector>
#include <algorithm> // for std::accumulate
#include <numeric>
#include <thread>
#include <functional> // for std::mem_fn
#include <chrono> // for system_clock::now()

template<typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);

    if (!length)
    {
        return init;
    }

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread -1)/min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = 
                    std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator block_start = first;
    for (unsigned long i=0; i<(num_threads-1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator, T>(), 
                                 block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }

    accumulate_block<Iterator, T>()(block_start, last, results[num_threads-1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), init);
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