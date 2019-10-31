#include <iostream> 
#include <filesystem> 

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <path>\n"; 
        return 1; 
    }

    const std::filesystem::path dir {argv[1]}; 

    if (!std::filesystem::exists(dir))
    {
        std::cout << "Path " << dir << " does not exist. \n"; 
        return 1; 
    }

    std::cout << std::filesystem::canonical(dir).c_str() << '\n';
}