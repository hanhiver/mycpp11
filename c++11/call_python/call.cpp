#include <iostream>
#include <string>
//#include <cstdio>
//#include <cstdlib> 

using namespace std; 

int call_shell(std::string& cmdstr, std::string& /*out*/ cmdoutput)
{
    enum { maxline = 1024 };
    char line[maxline];
    cmdoutput.clear();

    FILE *fpin;
    int ret;
    if ((fpin = popen(cmdstr.c_str(), "r")) == NULL)
    {
        std::cout << "popen error. \n";
        return -1;
    }

    for (;;)
    {
        if (fgets(line, maxline, fpin) == NULL)
        {
            break; 
        }
        cmdoutput += line; 
    }

    ret = pclose(fpin);
    if(ret == -1)
    {
        printf("pclose error. \n");
        return -1;
    }

    return ret; 
}

int main(int argc, char* argv[])
{
    string cmd = "ls";
    string cmdoutput; 

    int ret = call_shell(cmd, cmdoutput);
    std::cout << "=====Output=====" << std::endl; 
    std::cout << cmdoutput;
    std::cout << "======END=======" << std::endl; 
    std::cout << "Return code: " << ret << std::endl;

    return ret; 
}