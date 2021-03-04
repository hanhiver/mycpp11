#include <iostream>
#include <string>
#include <boost/regex.hpp>

using namespace std;

int main()
{
    boost::regex date_reg("^[0-9]{4}-(((0?[13578]|(10|12))-(0?[1-9]|[1-2][0-9]|3[0-1]))|(0?2-(0?[1-9]|[1-2][0-9]))|((0?[469]|11)-(0?[1-9]|[1-2][0-9]|30)))$");
    std::string date = "2021-03-01";

    bool result = false; 
    try
    {
        result = boost::regex_match(date, date_reg); 
    }
    catch(std::runtime_error)
    {
        std::cerr << "Error on phase: " << date << std::endl; 
    }
    std::cout << (result ? "valid" : "invalid") << std::endl;
    return 0;
}