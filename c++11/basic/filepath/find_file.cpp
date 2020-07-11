#include <iostream> 
#include <string> 

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int find_file(std::string& location, /*out*/ std::string& found_path)
{
    DIR* dp;
    struct dirent* dirp; 
    struct stat st; 
}