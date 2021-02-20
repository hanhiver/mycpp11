/*
#ifndef __POPEN_SINGLE_H__
#define __POPEN_SINGLE_H__

#define MAXBUFFSIZE 1024

enum POPEN_ERROR_CODE
{
    POPEN_OPEN_FAILED = -1,
    POPEN_FORK_FAILED = -2,
    POPEN_EXEC_CMD_FAILED = -3
};

#include <string> 

class PopenSingle
{
public:
    static PopenSingle& GetInstance();
    static int popen(const std::string &cmd, std::string &result);
    static int popen2(const std::string &cmd, std::string &result);

private:
    PopenSingle();
    ~PopenSingle();
};

#endif // __POPEN_SINGLE_H__
*/
#include <cstdio>
#include "popen_single.h"

PopenSingle::PopenSingle()
{
}

PopenSingle::~PopenSingle()
{
}

PopenSingle& PopenSingle::GetInstance()
{
    static PopenSingle instance; 
    return instance; 
}

int PopenSingle::spopen(const std::string &cmd, std::string &result)
{
    FILE* fd = popen(cmd.c_str(), "r");
    if(NULL == fd)
    {
        return POPEN_OPEN_FAILED; 
    }
    char buf[MAXBUFFSIZE] = {'\0'};
    
    int ret = fread(buf, sizeof(buf), 1, fd);
    if (ret >= 0)
    {
        result = buf; 
    }

    if(0 != pclose(fd))
    {
        result += "pclose failed";
    }

    return ret >= 0 ? 0 : -1;
}

int PopenSingle::spopen2(const std::string &cmd, std::string &result)
{
    std::string append_cmd = cmd + std::string("; echo \"Ret code:\"$?");
    FILE* fd = popen(append_cmd.c_str(), "r");
    if(NULL == fd)
    {
        return POPEN_OPEN_FAILED; 
    }
    char buf[MAXBUFFSIZE] = {'\0'};
    
    while(fgets(buf, MAXBUFFSIZE, fd) != NULL)
    {
        result += std::string(buf);
    }

    if(0 != pclose(fd))
    {
        result += "pclose failed";
    }

    int ret = 0;
    if (std::string::npos == result.find("Ret code:0"))
    {
        ret = POPEN_EXEC_CMD_FAILED;
    }
    
    return ret;
}