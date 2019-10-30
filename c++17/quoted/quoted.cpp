#include <iostream> 
#include <iomanip> 
#include <sstream> 

int main()
{
    std::stringstream ss; 
    std::string in = "string with spaces and \"quotes\" too.";
    std::string out; 

    ss << std::quoted(in); 
    std::cout << "Raw string  [" << in << "]\n";
    std::cout << "Read in     [" << in << "]\n"
              << "Stored as   [" << ss.str() << "]\n";
    
    ss >> std::quoted(out);
    std::cout << "Written out [" << out << "]\n"; 
}