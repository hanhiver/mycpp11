#ifndef __POPEN_SINGLE_H__
#define __POPEN_SINGLE_H__

#define MAXBUFFSIZE 65535

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
    static int spopen(const std::string &cmd, std::string &result);
    static int spopen2(const std::string &cmd, std::string &result);

private:
    PopenSingle();
    ~PopenSingle();
};

#endif // __POPEN_SINGLE_H__