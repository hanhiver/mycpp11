#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib> 

using namespace std; 

int shell_cal(std::string& cmdstr)
{
    enum { maxline = 100 };
    char line[maxline];

    FILE *fpin;
    int ret;
    if ((fpin = popen(cmdstr.c_str(), "r")) == NULL)
    {
        std::cout << "popen error. \n";
        exit(-1);
    }

    for (;;)
    {
        fputs("prompt> ", stdout);
        fflush(stdout);
        if (fgets(line, maxline, fpin) == NULL)
        {
            break; 
        }
        if (fputs(line, stdout) == EOF)
        {
            printf("fputs error. \n");
            exit(-1);
        }
    }

    ret = pclose(fpin);
    if(ret == -1)
    {
        printf("pclose error. \n");
        exit(-1);
    }

    return ret; 
}

int main(int argc, char* argv[])
{
    string cmd = argv[1];
    int ret = shell_cal(cmd);

    return ret; 
}