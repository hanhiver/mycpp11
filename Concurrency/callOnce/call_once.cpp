#include <iostream>
#include <thread> 
#include <vector>
#include <mutex>

class initOnce
{
private:
    std::vector<int> vect;
    mutable std::once_flag init_flag;

    void init_vect()
    {
        for (int i=1; i<5; ++i)
        {
            vect.push_back(i);
            vect.push_back(i-1);
        }
    }

public:
    initOnce()
    {
        //init_vect();
    }

    void print()
    {
        std::call_once(init_flag, &initOnce::init_vect, this);
        for (auto& elem : vect)
        {
            std::cout << elem << "\t";
        }
        std::cout << std::endl;
    }
};

int main()
{
    initOnce io; 
    //io.print();
    
    std::vector<std::thread> threads;

    for (int i=0; i<4; ++i)
    {
        threads.push_back(std::move(std::thread(io.print)));
    }

    for (auto& t : threads)
    {
        t.join();
    }
}
