#include <iostream>
#include <string> 

#include "popen_single.h"

int main()
{
    std::string cmd = "find /usr";
    std::string result; 
    int status = PopenSingle::GetInstance().spopen(cmd, result);

    if (POPEN_OPEN_FAILED == status || POPEN_FORK_FAILED == status || POPEN_EXEC_CMD_FAILED == status)
    {
        perror("popen failed");
    }

    std::cout << result << std::endl;

    return status;
}