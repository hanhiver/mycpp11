#include <iostream>
#include <iomanip>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


bool is_any_of(const std::string& json_str, const std::string& in)
{
    json j;
    try
    {
        j = nlohmann::json::parse(json_str.c_str());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << j.size() << ", type: " << (j.type() == json::value_t::array) << std::endl; 
    std::cout << j.size() << ", type: " << (j.type() == json::value_t::string) << std::endl; 
    /*
    if (j.type() == json::value_t::string)
    {
        std::cout <<  << std::endl; 
    }
    else if (j.type() == json::value_t::array)
    {
        for (const auto& item : j.items())
        {
            std::cout << item.value() << std::endl;
            
            if (item.value() == in)
            {
                return true; 
            }
            
        }

        return false; 
    }
    else
    {
        return false; 
    }
    */
    return true; 
}

int main()
{
    std::string one = "one";
    std::string two = R"(["two"])";
    std::string one_two = R"(["one", "two"])";

    std::string test = R"(
        {
            "str" : "test_str",
            "ary" : ["one", "two"]
        }
    )";

    json j = "hello";
    try
    {
        j = nlohmann::json::parse(test.c_str());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << j.dump(4) << std::endl; 

    std::cout << j.at("str").size() << ", " << (j.at("str") == json::value_t::string) << std::endl; 
    std::cout << j.at("ary").size() << ", " << (j.at("str") == json::value_t::array) << std::endl; 
    //std::cout << is_any_of(one_two, "one") << std::endl; 
    //std::cout << is_any_of(one, "one") << std::endl; 
}