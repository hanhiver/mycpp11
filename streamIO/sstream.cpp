#include <iostream>
#include <sstream>
#include <bitset>
using namespace std; 

int main()
{
    ostringstream os;

    // decimal and hexadecimal value. 
    os << "dec: " << 15 << hex << " hex: " << 15 << endl;
    cout << os.str() << endl;

    // append floating value and bitset
    bitset<15> b(5678);
    os << "float: " << 4.67 << " bitset: " << b << endl;
    os.seekp(0);
    os << "oct: " << oct << 15; 
    cout << os.str() << endl; 
}