#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

int main()
{
    std::string src = "{\"cipherText\":\"jX+gJoePAEZS0obecVJ/7SAbhVmAPlI5Y5g5O8xHUDJaGn4sLK4WBdr4AdAdT66oP4B1i+zEoP2x9oh4yQq4YxaJg4ctEYlFY/39C1HJeqRlhhaI5Q7MPz/ZjgMk1HO4dYSG5MNJn3Qk0QUsAY1iAZot0N2SUCJVG5tEnVbejbc=\",\"curTime\":1602588274,\"funcNameList\":[],\"keyInfo\":{\"keyIndex\":\"1234-5678-abcd\",\"keyType\":\"RSA\"},\"vendorName\":\"miaoxiu\",\"version\":1}";
    //nlohmann::json j; 
    auto j = nlohmann::json::parse(src); 
    //json.parse(src.c_str());
    //j.accept(src);
    std::cout << std::setw(4) << j << "\n";
    return 0;
}