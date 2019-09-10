#include <string>
#include <regex>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    string data = "XML tag: <tag-name>the Value</tag-name>.";
    cout << "data:                   " << data << "\n\n";

    smatch m;
    bool found = regex_search(data, m, regex("<(.*)>(.*)</(\\1)>"));

    // print match details: 
    cout << "m.empty():              " << boolalpha << m.empty() << endl;
    cout << "m.size():               " << m.size() << endl;

    if (found)
    {
        cout << "m.str():                " << m.str() << endl;
        cout << "m.length():             " << m.length() << endl;
        cout << "m.position():           " << m.position() << endl;
        cout << "m.prefix().str():       " << m.prefix().str() << endl;
        cout << "m.suffix().str():       " << m.suffix().str() << endl;
        cout << endl;

        for (uint i=0; i<m.size(); ++i)
        {
            cout << "m[" << i << "].str():             " << m[i].str() << endl;
            cout << "m.str(" << i << "):               " << m.str(i) << endl;
            cout << "m.position(" << i << "):          " << m.position(i) << endl;
        }
        cout << endl;

        // iterating over all matches (using iterator):
        cout << "matches:" << endl;
        for (auto pos = m.begin(); pos != m.end(); ++pos) 
        {
            cout << " " << *pos << " ";
            cout << "(length: " << pos->length() << ")" << endl;
        }
    }

}