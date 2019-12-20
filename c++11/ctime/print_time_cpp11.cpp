#include <iostream> 
#include <chrono>
#include <ctime> 

int main()
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&t);

    std::cout << "ASC Time: " << std::asctime(now_tm) << std::endl; 

}
