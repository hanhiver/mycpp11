#include <iostream> 
#include <ctime> 

int main()
{
    time_t rawtime; 
    struct tm* timeinfo; 

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    std::cout << "Time: " << asctime(timeinfo) << std::endl; 
    return 0; 
}