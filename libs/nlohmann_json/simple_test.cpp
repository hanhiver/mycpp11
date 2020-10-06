#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    // 创建一个JSON
    json j =
    {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {
            "answer", {
                {"everything", 42}
            }
        },
        {"list", {1, 0, 2}},
        {
            "object", {
                {"currency", "USD"},
                {"value", 42.99}
            }
        }
    };

    // 添加一个值
    j["new"]["key"]["value"] = {"another", "list"};

    // 计算有元素数目。
    auto s = j.size();
    j["size"] = s;

    // 用4个空格作为缩进打印JSON
    std::cout << std::setw(4) << j << '\n';

    // 创建JSON数组
    json j_no_init_list = json::array();
    json j_empty_init_list = json::array({});
    json j_nonempty_init_list = json::array({1, 2, 3, 4});
    json j_list_of_pairs = json::array({ {"one", 1}, {"two", 2} });

    // 序列化JSON数组
    std::cout << j_no_init_list << '\n';
    std::cout << j_empty_init_list << '\n';
    std::cout << j_nonempty_init_list << '\n';
    std::cout << j_list_of_pairs << '\n';

    // 一个有效的JSON结构
    auto valid_text = R"(
    {
        "numbers": [1, 2, 3]
    }
    )";

    // 一个无效的JSON结构
    auto invalid_text = R"(
    {
        "strings": ["extra", "comma", ]
    }
    )";

    std::cout << std::boolalpha
              << "valid_text是否有效：" << json::accept(valid_text) << '\n'
              << "invalid_text是否有效：" << json::accept(invalid_text) << '\n';
}