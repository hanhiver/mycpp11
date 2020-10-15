#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

int main()
{
    std::string src = "{\"status\":200,\"msg\":\"success\",\"data\":{\"version\":1,\"reqUuid\":\"8fc5095ca5b347a6ab79bb69f8ed420f\",\"reportCountDown\":453,\"authResult\":null,\"authMessage\":null,\"signature\":\"nY8z99y6FyXE37szSlByOGohwZI6vZKLF69TZz0M6I7NeSMp7M0yVYDSh1gw0+FsD+0TdD09ms4c\\r\\nUhU8D5AavZDFks8W9nWIl04llMnLisx020L4goaczEUbl5wWwgCBK63YdTn/UnwxWgB0Qxc533pC\\r\\ny+k/mV27FCgMS+xpeiY=\\r\\n\"}}";
    //nlohmann::json j; 
    auto j = nlohmann::json::parse(src); 
    //json.parse(src.c_str());
    //j.accept(src);
    std::cout << "src: " << src << std::endl; 
    std::cout << std::setw(4) << j << "\n";

    int version; 
    version = j.at("data").at("version");
    std::cout << "VERSION: " << version << std::endl; 
    return 0;
}