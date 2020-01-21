#include <iostream> 
#include <string> 
#include <boost/regex.hpp>

/*
bool is_valid_filename1(const std::string& filename)
{
    //std::regex reg(R"(^[^+-./\t\b@#$%*()\[\]][^/\t\b@#$%*()\[\]]{1,254}$)");
    boost::regex reg(R"(^[^+-./\t\b@#$%*()\[\]][^/\t\b@#$%*()\[\]]{1,254}$)");
    
    bool found = boost::regex_match(filename, reg);
    return found; 
}
*/
// Function to check if the input filename is a valid UNIX filename. 
bool is_valid_filename(const std::string& filename)
{
    // Here we only allow the max length of the file name to 248 chars 
    // in order to reserve space for "/tmp"
    boost::regex reg(R"(^[^+-./\t\b@#$%*()\[\]][^/\t\b@#$%*()\[\]]{1,248}$)");
    bool result = false; 
    try
    {
        result = boost::regex_match(filename, reg); 
    }
    catch(std::runtime_error)
    {
        std::cerr << "Error on phase filename: " << filename << std::endl; 
    }
    
    return result;  
}

int main()
{
    std::vector<std::string> test_cases {
        "ok.txt", 
        "[abc].txt", 
        "...txt",
        "/tmp/cams.txt", 
        ""
        };
    
    for (auto& item : test_cases)
    {
        std::cout << item << " is valid filename: "
                  << std::boolalpha 
                  << is_valid_filename(item)
                  << std::endl; 
    }

    return 0; 
}