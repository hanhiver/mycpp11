#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
    double x, y; 

    cout << "Multiplication of two floating point values" << endl;

    cout << "first operand:  "; 
    if (! (cin >> x))
    {
        // input error
        // ==> error message and exit program with error status. 
        cerr << "error while reading the first floating value" << endl;
        return EXIT_FAILURE;
    }

    cout << "second operand: "; 
    if (! (cin >> y))
    {
        // input error
        // ==> error message and exit program with error status. 
        cerr << "error while reading the first floating value" << endl;
        return EXIT_FAILURE;
    }

    cout << x << " times " << y << " equals " << x*y << endl;
    cout << endl;
}