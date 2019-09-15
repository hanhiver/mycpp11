#include <string>
#include <regex>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    string data = "<person>\n"
                  " <first>Nico</first>\n"
                  " <last>Josuttis</last>\n"
                  "</person>\n";

    regex reg("<(.*)>(.*)</(\\1)>");

    //iterator over all matches. 
    // {0, 2}: 0: full match, 2: second substring. 
    // 0 means first we match the whole string. 
    // 2 means second we match the second string. 
    sregex_token_iterator pos(data.cbegin(), data.cend(), reg, {0, 2});
    sregex_token_iterator end;

    for (; pos!=end; ++pos)
    {
        cout << "match:     " << pos->str() << endl; 
    }
    cout << endl;

    string names = "nico, jim, helmut, paul, tim, john paul, rita";
    // seperate by ,; or . and spaces. 
    regex sep("[ \t\n]*[,;.][ \t\n]*");
    // -1: values between separators. 
    sregex_token_iterator p(names.cbegin(), names.cend(), sep, -1);
    
    for (; p!=end; ++p)
    {
        cout << "name:      " << *p << endl;
    }
    cout << endl;
}