#include <future>
#include <mutex>
#include <iostream>
#include <chrono> 
#include <string> 

std::mutex printMutex;

void print(const std::string& s)
{
    for (char c : s)
    {
        std::cout.put(c);
    }
    std::cout << std::endl;
}

void print_lock(const std::string& s)
{
    std::lock_guard<std::mutex> l(printMutex);
    {
        for (char c : s)
        {
            std::cout.put(c);
        }
        std::cout << std::endl;
    } // ensure the lock l unlock here. 
}

int main()
{   
    std::cout << "Run WITHOUT lock: " << std::endl; 
    auto f1 = std::async(std::launch::async, print, 
                         "Hello from a first thread. ");
    auto f2 = std::async(std::launch::async, print, 
                         "Hello from a second thread. ");
    print("Hello from the main thread. ");
    std::cout << std::endl; 

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << std::endl << std::endl; 

    std::cout << "Run WITH the lock: " << std::endl;
    auto f3 = std::async(std::launch::async, print_lock, 
                         "Greeting from a first thread. ");
    auto f4 = std::async(std::launch::async, print_lock, 
                         "Greeting from a second thread. ");
    print_lock("Greeting from the main thread. ");
    
}