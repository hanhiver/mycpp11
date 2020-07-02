#include <iostream> 
#include <string> 

#include <dirent.h>
#include <sys/stat.h>
//#include <unistd.h>
//#include <stdio.h>

int list_files(std::string dirname)
{
    DIR* dp; 
    struct dirent* dirp;
    struct stat st; 

    // Open the directory dirent. 
    dp = opendir(dirname.c_str());
    if (dp == NULL)
    {
        perror("Opendir failed. ");
        return -1; 
    }

    // Read all files in this dir. 
    while((dirp = readdir(dp)) != NULL) 
    {
        std::string fullname = dirname; 
        fullname += "/";
        fullname += dirp->d_name; 

        if(stat(fullname.c_str(), &st) == -1)
        {
            perror("Stat file failed.");
            return -1; 
        }
        
        if (S_ISDIR(st.st_mode))
        {
            std::cout << "DIR  - ";
        }
        else
        {
            std::cout << "FILE - ";
        }
        
        std::cout << dirp->d_name << std::endl; 
    }

    return 0; 
}

int main(int argc, char* argv[])
{
    list_files("/home/dhan/temp");

    return 0; 
}
