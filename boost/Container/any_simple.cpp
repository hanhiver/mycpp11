#include <iostream> 
#include <list> 
#include <string>
#include <boost/any.hpp>

using boost::any_cast; 
typedef std::list<boost::any> many; 

void append_int(many& values, int value)
{
    boost::any to_append = value; 
    values.push_back(to_append); 
}

void append_string(many& values, const std::string& value)
{
    values.push_back(value);
}

void append_char_ptr(many& values, const char* value)
{
    values.push_back(value);
}

void append_any(many& values, const boost::any& value)
{
    values.push_back(value);
}

void append_nothing(many& values)
{
    values.push_back(boost::any());
}

bool is_empty(const boost::any& operand)
{
    return operand.empty(); 
}

bool is_int(const boost::any& operand)
{
    return operand.type() == typeid(int);
}

bool is_char_ptr(const boost::any& operand)
{
    try
    {
        
        any_cast<const char *>(operand);
        return true;
    }
    catch(const boost::bad_any_cast&)
    {
        return false;
    }
}

bool is_string(const boost::any& operand)
{
    return any_cast<std::string>(&operand);
}

void count_all(many & values, std::ostream & out)
{
    out << "#empty == "
        << std::count_if(values.begin(), values.end(), is_empty) << std::endl;
    out << "#int == "
        << std::count_if(values.begin(), values.end(), is_int) << std::endl;
    out << "#const char * == "
        << std::count_if(values.begin(), values.end(), is_char_ptr) << std::endl;
    out << "#string == "
        << std::count_if(values.begin(), values.end(), is_string) << std::endl;
}

int main()
{
    /*
    std::cout << typeid(int).name() << std::endl; 
    std::cout << typeid(double).name() << std::endl;
    std::cout << typeid(std::string).name() << std::endl;  
    std::string str {"hello"};
    std::cout << typeid(str).name() << std::endl;
    */
    many s; 
    append_int(s, 1);
    append_char_ptr(s, "hello");
    std::string str{"world"};
    append_string(s, str);
    append_nothing(s);
    
    for (auto& item : s)
    {
        std::cout << "item: " << item.type().name() << ", " 
                  << "is_empty: " << std::boolalpha << is_empty(item) << ", "
                  << "is_int: " << std::boolalpha << is_int(item) << ", "
                  << "is_char_ptr: " << std::boolalpha << is_char_ptr(item) << ", " 
                  << "is_string: " << std::boolalpha << is_string(item) << std::endl; 
    }

    return 0;
}