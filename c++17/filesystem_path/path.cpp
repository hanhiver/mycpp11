#include <iostream> 
#include <filesystem> 

using namespace std;
using namespace std::filesystem; 

int main()
{
    path p {"testdir/foobar.txt"};

    cout << "Current_path    : " << current_path() << "\n"
         << "absolute_path   : " << absolute(p) << "\n"
         //<< "system_complete : " << system_complete(p) << "\n"
         << "canonical(p)    : " << canonical(p) << "\n";

    cout << path {"testdir"} / "foobar.txt" << "\n"; 

    /*
    cout << "canonical testdir : "
         << canonical("foobar.txt", (current_path()/"testdir")) << '\n'
         << "\ncanonical testdir 2 : "
         << canonical(p, current_path()/"testdir/..") << '\n'; 
    */
    cout << "equivalence: " << boolalpha
         << equivalent("testdir/foobar.txt", 
                       "testdir/../testdir/foobar.txt") << '\n';
}