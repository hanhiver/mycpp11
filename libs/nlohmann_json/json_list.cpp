#include <iostream>
#include <iomanip>
#include <unordered_map>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main()
{
    // 创建一个JSON
    json j;

    //j["version"] = "1.0.0.1";

    std::unordered_map<std::string, unsigned int> map1 { {"one", 1}, {"two", 2}, {"three", 3} };
    std::unordered_map<std::string, unsigned int> map2 { };
    
    j["funcNameList"] = json::value_t::array;

    int i = 0; 
    for (const auto& item : map1)
    {
        j["funcNameList"][i]["funcName"] = item.first;
        j["funcNameList"][i]["callCount"] = item.second;
        i++;
    }

    // 用4个空格作为缩进打印JSON
    std::cout << std::setw(4) << j << '\n';
    return 0;
}


    