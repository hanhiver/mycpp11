#include <iostream> 
#include <vector>
#include <thread> 
#include <chrono>

class join_threads
{
private:
    std::vector<std::thread>& _threads;

public:
    join_threads(std::vector<std::thread>& threads) : _threads(threads)
    {}
    
    void join()
    {
        for (auto& thread : _threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }

    ~join_threads()
    {
        for (auto& thread : _threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }
};

void hello(int idx)
{
    std::cout << "#" << idx << ", hello! " << std::endl; 
}

int main()
{
    std::cout << "=== For loop ===" << std::endl; 
    for (int i=0; i<5; i++)
    {
        hello(i);
    }
    std::cout << std::endl; 

    std::cout << "=== Multi-thread ===" << std::endl; 

    std::vector<std::thread> threads1;
    join_threads joiner1(threads1);

    for (int i=0; i<5; i++)
    {
        std::thread t = std::thread(hello, i); 
        threads1.push_back(std::move(t));
    }

    std::cout << "=== Inner Func ===" << std::endl; 

    std::vector<std::thread> threads2;
    join_threads joiner2(threads2);
    std::vector<int> vtest;

    for (int i=0; i<50; i++)
    {
        std::thread t = std::thread([&](int i)
        {
            std::cout << "#" << i << ", inner_hello! " << std::endl; 
            vtest.push_back(i);
        }, i); 
        threads2.push_back(std::move(t));
    }

    joiner2.join();
    //std::this_thread::sleep_for(std::chrono::seconds(1));   

    for (auto item : vtest)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl; 

    return EXIT_SUCCESS;
}