#include <iostream> 
#include <thread> 
#include <mutex> 

using namespace std::chrono_literals;

std::mutex mut_a; 
std::mutex mut_b; 

static void deadlock_func_1()
{
    std::cout << "bad f1 acquiring mutex a..." << std::endl; 
    std::lock_guard<std::mutex> la {mut_a};

    std::this_thread::sleep_for(100ms); 
    
    std::cout << "bad f1 acquiring mutext b..." << std::endl; 
    std::lock_guard<std::mutex> lb {mut_b}; 

    std::cout << "bad f1 got both mutexes. " << std::endl; 
}

static void deadlock_func_2()
{
    std::cout << "bad f2 acquiring mutex b..." << std::endl; 
    std::lock_guard<std::mutex> lb {mut_b};

    std::this_thread::sleep_for(100ms); 
    
    std::cout << "bad f2 acquiring mutext a..." << std::endl; 
    std::lock_guard<std::mutex> la {mut_a}; 

    std::cout << "bad f2 got both mutexes. " << std::endl; 
}

static void sane_func_1()
{
    std::scoped_lock l {mut_a, mut_b};
    std::cout << "sane f1 got both mutexes. " << std::endl; 
}
static void sane_func_2()
{
    std::scoped_lock l {mut_b, mut_a};
    std::cout << "sane f2 got both mutexes. " << std::endl; 
}

int main()
{
    {
        std::thread t1 {sane_func_1}; 
        std::thread t2 {sane_func_2}; 

        t1.join();
        t2.join();
    }

    {
        std::thread t1 {deadlock_func_1};
        std::thread t2 {deadlock_func_2};

        t1.join();
        t2.join(); 
    }
}