#include <iostream>
#include <string>

using namespace std; 

int shell_cal(std::string& cmdstr)
{
    enum { maxline = 1024 };
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
        if (fgets(line, maxline, fpin) == NULL)
        {
            break; 
        }
        fputs(">> ", stdout);
        fflush(stdout);
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

int shell_cal2(std::string& cmdstr)
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
        fputs(">> ", stdout);
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
    string cmd = "ls";
    int ret = shell_cal(cmd);
    std::cout << "Return code: " << ret << std::endl; 

    ret = system(cmd.c_str());
    std::cout << "Return code: " << ret << std::endl; 

    return ret; 
}