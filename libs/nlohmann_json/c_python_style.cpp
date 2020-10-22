// 测试部分转义字符串送进去parse的时候出错的情况。 
#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::string jstr1 = R"({"model_config":{"setPth":"/root/work/monocell/models/setting_det_seg.json"}})";

    std::string jstr2 = R"({"model_config":{\"setPth\":\"/root/work/monocell/models/setting_det_seg.json\"}})"; 

    // 创建一个JSON
    json j;

    std::cout << "原始字符串1： \n" << jstr1 << std::endl;  
    try
    {
        j = nlohmann::json::parse(jstr1.c_str());
    }
    catch(nlohmann::detail::exception& e)
    {
        std::cout << e.what(); 
    }
    std::cout << std::setw(4) << j << '\n';

    json q;
    std::cout << "原始字符串2： \n" << jstr2 << std::endl;  
    try
    {
        q = nlohmann::json::parse(jstr2.c_str());
    }
    catch(nlohmann::detail::exception& e)
    {
        std::cout << e.what(); 
    }
    std::cout << std::setw(4) << q << '\n';

    return 0;
}