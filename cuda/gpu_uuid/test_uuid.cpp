#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <sstream>

#include "uuid.h"

int main(int argc, char **argv)
{
        
    std::string uuid; 
    bool ret = get_1st_gpu_uuid(uuid);
    if (!ret)
    {
        return -1;
    }
    std::cout << "UUID: " << uuid << std::endl;

	return 0;
}
