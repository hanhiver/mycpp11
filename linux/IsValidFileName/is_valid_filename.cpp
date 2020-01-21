#include <iostream> 
#include <string> 
#include <regex> 

bool is_valid_filename(const std::string& filename)
{
    //std::regex reg(R"(^[^+-./\t\b@#$%*()\[\]][^/\t\b@#$%*()\[\]]{1,254}$)");
    std::regex reg(R"(^[^+-./\t\b@#$%*()\[\]][^/\t\b@#$%*()\[\]]{1,254}$)");
    
    bool found = regex_match(filename, reg);
    return found; 
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