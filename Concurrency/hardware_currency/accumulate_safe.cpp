#include <iostream>
#include <vector>
#include <algorithm> // for std::accumulate
#include <numeric>
#include <thread>
#include <functional> // for std::mem_fn
#include <chrono> // for system_clock::now()
#include <future> // for future

/*
template<typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last)
    {
        return std::accumulate(first, last, T());
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

    std::vector<std::future<T>> futures(num_threads - 1);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator block_start = first;
    for (unsigned long i=0; i<(num_threads-1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        std::packaged_task<T(Iterator, Iterator)> task(accumulate_block<Iterator, T>());
        //std::packaged_task<T(Iterator, Iterator)> task(accumulate_block<Iterator, T>());
        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task), block_start, block_end);
        block_start = block_end;
    }
    T last_result = accumulate_block()(block_start, last);

    std::for_each(threads.begin(), threads.end(), 
                  std::mem_fn(&std::thread::join));

    T result = init;
    for (unsigned long i=0; i<(num_threads-1); ++i)
    {
        result += futures[i].get();
    }

    result += last_result;
    return result;
}*/
template<typename Iterator,typename T>
struct accumulate_block
{
    T operator()(Iterator first,Iterator last)
    {
        return std::accumulate(first,last,T());
    }
};

template<typename Iterator,typename T>
T parallel_accumulate(Iterator first,Iterator last,T init)
{
    unsigned long const length=std::distance(first,last);

    if(!length)
        return init;

    unsigned long const min_per_thread=25;
    unsigned long const max_threads=
        (length+min_per_thread-1)/min_per_thread;

    unsigned long const hardware_threads=
        std::thread::hardware_concurrency();

    unsigned long const num_threads=
        std::min(hardware_threads!=0?hardware_threads:2,max_threads);

    unsigned long const block_size=length/num_threads;

    std::vector<std::future<T> > futures(num_threads-1);
    std::vector<std::thread> threads(num_threads-1);

    Iterator block_start=first;
    for(unsigned long i=0;i<(num_threads-1);++i)
    {
        Iterator block_end=block_start;
        std::advance(block_end,block_size);
        //auto ab_tmp = accumulate_block<Iterator, T>();
        std::packaged_task<T(Iterator,Iterator)> task(std::move(accumulate_block<Iterator,T>()));
        //std::packaged_task<T(Iterator,Iterator)> task(ab_tmp);
        futures[i]=task.get_future();
        threads[i]=std::thread(std::move(task),block_start,block_end);
        block_start=block_end;
    }
    auto ab = accumulate_block<Iterator, T>();
    T last_result=ab(block_start,last);

    std::for_each(threads.begin(),threads.end(),
                  std::mem_fn(&std::thread::join));

    T result=init;
    for(unsigned long i=0;i<(num_threads-1);++i)
    {
        result+=futures[i].get();
    }
    result += last_result;
    return result;
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