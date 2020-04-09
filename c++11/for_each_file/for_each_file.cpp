#include <iostream>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include <cstring>
#include <dirent.h>

using file_filter_type = std::function<bool(const char*, const char*)>;

inline bool is_folder(const char* dir_name)
{
    if (nullptr == dir_name)
    {
        throw std::invalid_argument("dir_name cannot be null. ");
    }
    auto dir = opendir(dir_name);
    if (dir)
    {
        closedir(dir);
        return true; 
    }

    return false;
}

inline char file_separator()
{
    return '/';
}

inline bool is_folder(const std::string& dir_name)
{
    if (dir_name.empty())
    {
        throw std::invalid_argument("dir_name cannot be empty. ");
    }
    return is_folder(dir_name.c_str());
}

static std::vector<std::string> for_each_file(const std::string dir_name, file_filter_type filter, bool sub=false)
{
    std::vector<std::string> v; 
    auto dir = opendir(dir_name.c_str());
    struct dirent* ent; 
    if (dir)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            auto p = std::string(dir_name).append({file_separator()}).append(ent->d_name);
            if (sub)
            {
                if ( 0 == std::strcmp(ent->d_name, "..") || 0 == std::strcmp(ent->d_name, "."))
                {
                    continue; 
                }
                else if (is_folder(p))
                {
                    auto r = for_each_file(p, filter, sub);
                    v.insert(v.end(), r.begin(), r.end());
                    continue; 
                }
            }

            if (sub || !is_folder(p))
            {
                if (filter(dir_name.c_str(), ent->d_name))
                {
                    v.emplace_back(p);
                }
            }
        }
        closedir(dir);
    }
    return v; 
}

const static file_filter_type default_ls_filter = [](const char*, const char*){
    return true;
};

inline std::vector<std::string> ls(const std::string& dir_name, bool sub=true)
{
    return for_each_file(dir_name, default_ls_filter, sub);
}

int main()
{
    std::string cur_dir = "..";
    auto file_list = ls(cur_dir);
    for (auto& item : file_list)
    {
        std::cout << item << std::endl; 
    }

    return 0; 
}
