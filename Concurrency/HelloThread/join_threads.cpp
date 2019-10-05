#include <iostream>
#include <vector>
#include <thread> 
#include <string> 

class join_threads
{
private:
    std::vector<std::thread> _threads;

public:
    join_threads(std::vector<std::thread>& threads) : _threads(threads)
    {}

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

void sayHello(int index, std::string str)
{
    std::cout << "#" << index << " Hello, " << str << std::endl; 
}

int main()
{
    std::vector<std::thread> threads;
    for (unsigned int i=0; i<5; ++i)
    {
        threads.push_back(std::move(std::thread(sayHello, i, "dhan")));
    }

    for (auto& elem : threads)
    {
        elem.join();
    }

    return 0;
}

