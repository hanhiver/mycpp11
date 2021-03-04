#include <regex>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    std::regex date_reg("^[0-9]{4}-(((0?[13578]|(10|12))-(0?[1-9]|[1-2][0-9]|3[0-1]))|(0?2-(0?[1-9]|[1-2][0-9]))|((0?[469]|11)-(0?[1-9]|[1-2][0-9]|30)))$");
    std::string date = "2021-03-01";
    bool ret = std::regex_match(date, date_reg);
    std::cout << (ret ? "valid" : "invalid") << std::endl;
    return 0;
}