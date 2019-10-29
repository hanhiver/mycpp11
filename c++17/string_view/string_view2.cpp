#include <iostream> 
#include <string_view> 

void print(std::string_view v)
{
    const auto words_begin (v.find_first_not_of(" \t\n"));
    v.remove_prefix(std::min(words_begin, v.size())); 

    const auto words_end (v.find_last_not_of(" \t\n")); 
    if (words_end != std::string_view::npos)
    {
        v.remove_suffix(v.size() - words_end -1);
    }

    std::cout << "length: " << v.length() 
              << " [" << v << "]" << std::endl; 
}

int main(int argc, char* argv[])
{
    using namespace std::literals; 
    print(argv[0]); 
    print({}); 
    print("a const char* array");
    print("an std::string_view literal"sv);
	print("an std::string instance"s);
    print(" \t\n foobar \n \t "); 

    char cstr[] {'a', 'b', 'c'};
	print(std::string_view(cstr, sizeof(cstr)));
}