#include <atomic> 
#include <iostream> 

using namespace std; 

int main()
{
    atomic<bool> check;

    cout << "\tCheck\t" << "Expect\t" << "Store?" << endl; 

    check = true; 
    bool expect = true; 
    cout << "before: " << boolalpha << check << "\t" << expect << endl;
    bool res = check.compare_exchange_weak(expect, false);
    cout << "after:  " << boolalpha << check << "\t" << expect << "\t" << res << endl;
    
    cout << endl; 

    check = true;
    expect = false; 
    cout << "before: " << boolalpha << check << "\t" << expect << endl;
    res = check.compare_exchange_weak(expect, false);
    cout << "after:  " << boolalpha << check << "\t" << expect << "\t" << res << endl;

}