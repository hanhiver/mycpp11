#include <iostream> 
#include <string> 
#include <fstream> 
#include <iomanip>
#include <cstdlib>

int main()
{
    std::ofstream file("test.txt.out");

    if(!file)
    {
        std::cerr << "Failed to open file test.txt.out. " << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<3; i++)
    {
        file << std::to_string(i) << ", " << "\n";
    }

    return 0;
}