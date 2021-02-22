#include <iostream> 
#include <sstream>
#include <iomanip>
#include <ctime> 
#include <chrono>


std::int64_t str_time_to_time_stamp(const std::string& time_str)
{
    std::tm tm = {};
    std::stringstream ss(time_str);
    //ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    ss >> std::get_time(&tm, "%Y-%m-%d");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    auto tmp = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
    return tmp.count();
}

std::chrono::system_clock::time_point str_time_to_time_point(const std::string& time_str)
{
    std::tm tm = {};
    std::stringstream ss(time_str);
    //ss >> std::get_time(&tm, "%Y-%m-%d");
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return tp;
}

int main()
{
    std::time_t t = std::time(NULL);
    std::tm tm = *std::localtime(&t);
    std::cout <<std::put_time(&tm, "%Y-%m-%d") << '\n';

    auto a = str_time_to_time_stamp("2020-01-01");
    auto b = str_time_to_time_stamp("2020-01-03");
    std::cout << "a: " << a << ", b: " << b << ", diff: " << b - a << std::endl; 

    return 0;
}