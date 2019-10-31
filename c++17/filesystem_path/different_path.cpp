#include <iostream> 
#include <filesystem> 

using namespace std; 
using namespace std::filesystem;

int main()
{
    path p {"/home/dhan/myprog/c_cpp/mycpp11/test.cpp"}; 

    cout << "full path       : " << p << '\n'; 
    cout << "root_path()     : " << p.root_path() << '\n'
         << "relative_path() : " << p.relative_path() << '\n'
         << "parent_path()   : " << p.parent_path() << '\n'
         << "filename()      : " << p.filename() << '\n'
         << "stem()          : " << p.stem() << '\n'
         << "extension()     : " << p.extension() << '\n'; 

    return 0; 
}