#include <iostream>
#include <vector>
#include <string> 

int main()
{
    std::vector<string> msg {"hello", "C++", "World", "from", "VS Code!"};

    for (const string& word : msg)
    {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}