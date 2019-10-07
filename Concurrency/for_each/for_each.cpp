#include <future> 
#include <thread> 
#include <algorithm>
#include <vector> 
#include <iostream> 

class join_threads
{
private:
    std::vector<std::thread>& _threads; 

public:
    join_threads(std::vector<std::thread>& threads) : 
        _threads(threads)
    {}

    ~join_threads()
    {
        for (unsigned int i=0; i<_threads.size(); ++i)
        {
            if (_threads[i].joinable())
            {
                _threads[i].join();
            }
        }
    }
};

template <typename Iterator, typename Func> 
void parallel_for_each(Iterator first, Iterator last, Func f)
{
    unsigned long const length = std::distance(first, last);

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread -1)/min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = 
                    std::min(hardware_threads!=0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads; 

    std::vector<std::future<void>> futures(num_threads - 1);
    std::vector<std::thread> threads(num_threads - 1);
    join_threads joiner(threads);

    Iterator block_start = first; 
    for (unsigned long i=0; i<(num_threads-1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        std::packaged_task<void(void)> task([=]
        {
            std::for_each(block_start, block_end, f);
        });
        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task));
        block_start = block_end;
    }

    std::for_each(block_start, last, f);
    for (unsigned long i=0; i<(num_threads-1); ++i)
    {
        futures[i].get();
    }
} 

double mix(double& d)
{
    d += d;
    d *= d; 
    return d;
}

int main()
{
    std::vector<double> vect; 
    for (double d=1.0; d<1000000.0; d+=1.0)
    {
        vect.push_back(d);
    }

    std::cout << "Normal for_each: " << std::endl; 
    auto start = std::chrono::system_clock::now();
    std::for_each(vect.begin(), vect.end(), mix);
    auto end = std::chrono::system_clock::now();

    auto dur = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
    double period = double(dur.count());
    std::cout << "Normal for each finished in " << period << " ms. " << std::endl;

    std::cout << std::endl; 
    vect.clear();
    for (double d=1.0; d<1000000.0; d+=1.0)
    {
        vect.push_back(d);
    }

    std::cout << "Parallel for_each: " << std::endl; 
    start = std::chrono::system_clock::now();
    parallel_for_each(vect.begin(), vect.end(), mix);
    end = std::chrono::system_clock::now();

    dur = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
    period = double(dur.count());
    std::cout << "Parallel for each finished in " << period << " ms. " << std::endl;

    return 0;
}