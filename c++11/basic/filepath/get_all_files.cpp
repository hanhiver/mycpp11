#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
extern "C"{
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <errno.h>
    #include <dirent.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
}
using namespace std;

/*
S_ISLNK(st_mode)：是否是一个连接.
S_ISREG(st_mode)：是否是一个常规文件.
S_ISDIR(st_mode)：是否是一个目录
S_ISCHR(st_mode)：是否是一个字符设备.
S_ISBLK(st_mode)：是否是一个块设备
S_ISFIFO(st_mode)：是否 是一个FIFO文件.
S_ISSOCK(st_mode)：是否是一个SOCKET文件 
*/

int get_all_files(const std::string& location, /*out*/ std::vector<std::string>& files)
{
    DIR* dp; 
    struct dirent* dirp; 
    struct stat st; 

    /* open dirent directory */
    if((dp = opendir(location.c_str())) == NULL)
    {
        perror("opendir");
        return -1;
    }

    while((dirp=readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name, ".")==0 || strcmp(dirp->d_name, "..")==0)
        {
            continue; 
        }
        else if(dirp->d_type == DT_REG) // Regular file. 
        {
            files.push_back(location + "/" + dirp->d_name);
        }
        else if(dirp->d_type == DT_LNK) // Link. 
        {
            continue; // not follow the link.
        }
        else if(dirp->d_type == DT_DIR)
        {
            //std::string sub_dir = location.copy() + "/" + dirp->d_name;
            get_all_files(location+"/"+dirp->d_name, files);
        }
    }

    closedir(dp);
    return 0;
}

void getAllFiles(string path, vector<string>& files)
{
    DIR *dir;
    struct dirent *ptr;
    if((dir=opendir(path.c_str()))==NULL){
        perror("Open dri error...");
        exit(1);
    }
    while((ptr=readdir(dir))!=NULL){
        if(strcmp(ptr->d_name,".")==0||strcmp(ptr->d_name,"..")==0)
            continue;
        else if(ptr->d_type==8)//file
            files.push_back(path+"/"+ptr->d_name);
        else if(ptr->d_type==10)//link file
            continue;
        else if(ptr->d_type==4){
            //files.push_back(ptr->d_name);//dir
            getAllFiles(path+"/"+ptr->d_name,files);
        }
    }
    closedir(dir);
}
int main(int argc,char **argv){
    
    /*
    if(argc<2){
        cout<<"USAGE:./a.out path"<<endl;
        exit(-1);
    }
    char * filePath = argv[1];
    */
    std::string filePath = "/home/dhan/Desktop";
    vector<string> files;
    //char * distAll = "allFiles.txt";
    //getAllFiles(filePath, files);
    get_all_files(filePath, files);
    for (auto& item : files)
    {
        std::cout << item << std::endl; 
    }
    /*
    ofstream ofn(distAll);
    int size = files.size();
    //ofn << size << endl;
    for (int i = 0; i<size; i++)
    {
        ofn << files[i] << endl;
    }
    ofn.close();
    */
    return 0;
}