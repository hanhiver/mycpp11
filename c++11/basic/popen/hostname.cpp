#include <iostream> 
#include <string> 
#include <stdio.h>

int main(int argc, char *argv[])
{
    std::string cmd = "hostname";
    FILE *in; 
    char buf[1025];
    
    if(!(in = popen(cmd.c_str(), "r")))
    {
        return -1;
    }

    while(fgets(buf, sizeof(buf), in) != NULL)
    {
        std::cout << buf; 
    }

    pclose(in);
    return 0;

}