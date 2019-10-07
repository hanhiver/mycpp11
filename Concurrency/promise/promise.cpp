#include <iostream> // std::cout, std::endl; 
#include <thread>   // std::thread
#include <string>   // std::string
#include <future>   // std::promise, std::future
#include <chrono>   // seconds

void read(std::future<std::string> *future)
{
    // Future will block untill its value set. 
    std::cout << future->get() << std::endl;
}

int main()
{
    // Promise is a producer here. 
    std::promise<std::string> promise; 

    // Future is a consumer here. 
    std::future<std::string> future = promise.get_future();

    // Start the read thread. 
    std::thread thread(read, &future);

    // Wait for a while. 
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Set the promise value. 
    promise.set_value("Hello future! \n");

    thread.join();

    return 0; 
}