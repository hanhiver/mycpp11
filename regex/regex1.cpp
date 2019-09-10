#include <regex>
#include <iostream>
using namespace std;

void out(bool b)
{
    cout << ( b ? "found" : "not found") << std::endl;
}

int main()
{
    bool found = false;

    // find XML/HTML-tagged value. 
    regex reg1("<.*>.*</.*>");
    found = regex_match("<tag>value</tag>", reg1);
    out(found);
    found = regex_match("<tag>value</tad>", reg1);
    out(found);

    // before and after value should match. 
    regex reg2("<(.*)>.*</\\1>");
    found = regex_match("<tag>value</tag>", reg2);
    out(found);
    found = regex_match("<tag>value</tad>", reg2);
    out(found);

    // grep syntax. 
    regex reg3("<\\(.*\\)>.*</\\1>", regex_constants::grep);
    found = regex_match("<tag>value</tag>", reg3);
    out(found);

    // Using c-string as regex. 
    found = regex_match("<tag>value</tag>", regex("<(.*)>.*</\\1>"));
    out(found);

    // match should match the whole string. 
    // search can match part of the string. 
    found = regex_match("XML tag: <tag>value</tag>", reg1);
    out(found);

    found = regex_search("XML tag: <tag>value</tag>", reg1);
    out(found);
    
}