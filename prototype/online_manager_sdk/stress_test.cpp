#include <iostream>
#include <thread> 
#include "sdk_manager.hpp"

const int LOOP_TIME = 1000000;

int main(int argc, char* argv[])
{
    
    if (AUTH_CODE::SUCCESS != SDKManager::Get().Init("/home/hd275562/myprog/mycpp11/prototype/online_manager_sdk/test.config"))
    {
        std::cout << "Initialization failed. " << std::endl;
        exit(-1);
    }

    /*
    std::this_thread::sleep_for(std::chrono::seconds(2));
    SDKManager::Get().Count("Func1", 1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    SDKManager::Get().Count("Func1", 1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    SDKManager::Get().Count("Func2", 1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    SDKManager::Get().Count("Func1", 1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    SDKManager::Get().Count("Func2", 10);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    */

    for(int i = 0; i < LOOP_TIME; ++i)
    {
        SDKManager::Get().Count("StressTest_817_16_1M", 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if (i%10000 == 0)
        {
            std::cout << "Now " << i << " SDK call count!" << std::endl;
        }
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Main thread Done. " << std::endl;
    SDKManager::Get().Shutdown();
}
