#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

//forward declarations. 
void writeCharsetToFile(const string& filename);
void outputFile(const string& filename);

int main()
{
    writeCharsetToFile("charset.out");
    outputFile("charset.out");
}

void writeCharsetToFile(const string& filename)
{
    // open output file. 
    ofstream file(filename);

    // file open? 
    if (! file)
    {
        // No, abort program. 
        cerr << "Cannot open output file \"" << filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    // write character set.
    for (int i=32; i<256; ++i)
    {
        file << "value: " << setw(3) << i << "     "
             << "char:  " << static_cast<char>(i) << endl;
    }
}

void outputFile(const string& filename)
{
    // output input file. 
    ifstream file(filename);

    // file open? 
    if (!file)
    {
        //No, abort program. 
        cerr << "Cannot open input file: \"" << filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    // copy file contents to cout. 
    char c;
    while (file.get(c))
    {
        cout.put(c);
    }

}



