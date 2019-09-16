#include <iostream> 
#include <fstream>
using namespace std;

void printFileTwice(const char* filename)
{
    // open file. 
    std::ifstream file(filename);

    // print contents the first time. 
    std::cout << file.rdbuf();

    // seek to the begining. 
    file.seekg(0);

    // print contents the second time. 
    std::cout << file.rdbuf();
}

int main(int argc, char* argv[])
{
    for (int i=1; i<argc; ++i)
    {
        printFileTwice(argv[i]);
    }
}