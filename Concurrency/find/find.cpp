#include <iostream> 
#include <future> 
#include <thread> 
#include <vector> 
#include <algorithm> 

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

template <typename Iterator, typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType match)
{
    struct find_element
    {
        void operator()(Iterator begin, Iterator end, 
                        MatchType match, 
                        std::promise<Iterator>* result, 
                        std::atomic<bool>* done_flag)
        {
            try
            {
                for (; (begin != end) && !done_flag->load(); ++begin)
                {
                    if (*begin == match)
                    {
                        result->set_value(begin);
                        done_flag->store(true);
                        return; 
                    }
                }
            }
            catch(...)
            {
                try
                {
                    result->set_exception(std::current_exception());
                    done_flag->store(true);
                }
                catch(...)
                {
                    // Do nothing. 
                }
                
            }
            
        }
    };

    unsigned long const length = std::distance(first, last);

    if (!length)
    {
        return last;
    }

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread)/min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads!=0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads;

    std::promise<Iterator> result;
    std::atomic<bool> done_flag(false);
    std::vector<std::thread> threads(num_threads - 1);
    
    // block to start and end all threads. 
    {
        join_threads jointer(threads);

        Iterator block_start = first;
        for (unsigned long i=0; i<(num_threads-1); ++i)
        {
            Iterator block_end = block_start;
            std::advance(block_end, block_size); 
            threads[i] = std::thread(find_element(), 
                                     block_start, block_end, match, 
                                     &result, &done_flag);
            block_start = block_end;
        }

        find_element()(block_start, last, match, &result, &done_flag);
    }

    if (!done_flag.load())
    {
        return last; 
    }

    return result.get_future().get();
}

int main()
{
    std::vector<long> vect; 
    for (unsigned long i=0; i<10000000; ++i)
    {
        vect.push_back(i);
    }
    unsigned long value = 8888888;

    auto start = std::chrono::system_clock::now(); 
    auto pos = std::find(vect.cbegin(), vect.cend(), value);
    auto end = std::chrono::system_clock::now(); 
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double period = double(dur.count());
    std::cout << "Normal Found 8888888: " << std::boolalpha << !(pos == vect.cend()) << " in " << period << " ms. " << std::endl; 

    std::cout << std::endl; 

    start = std::chrono::system_clock::now(); 
    pos = parallel_find(vect.cbegin(), vect.cend(), value);
    end = std::chrono::system_clock::now(); 
    dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    period = double(dur.count());
    std::cout << "Parallel Found 8888888: " << std::boolalpha << !(pos == vect.cend()) << " in " << period << " ms. " << std::endl; 
    
    return 0;
}