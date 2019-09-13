#include <iostream> 
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    ifstream file;

    // fro all command-line arguments
    for (int i=1; i<argc; ++i)
    {
        // open file. 
        file.open(argv[i]);

        // write file contents to cout
        char c;
        while (file.get(c))
        {
            cout.put(c);
        }

        // clear eofbit and failbit set due to end of file. 
        file.clear();
        file.close();
    }    
}
