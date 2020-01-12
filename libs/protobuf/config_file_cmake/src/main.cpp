#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <string> 
#include <fstream> 

#include "test.pb.h"
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h> 

#include <unistd.h> 
#include <string.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h> 
#include <stdlib.h> 

int main(void)
{
    // 1. Serilize, fill the basic configuration items. 
    msgType::ProtoTest cpt1; 
    cpt1.set_int32_test(123);
    cpt1.set_str_test("handong");
    cpt1.add_dou_test(56.023);
    cpt1.add_dou_test(79.239);

    msgType::ProtoTestSub* pt = cpt1.add_sub_test(); 
    pt->set_test1(12);
    pt->set_test2("hello");
    pt = cpt1.add_sub_test(); 
    pt->set_test1(34); 
    pt->set_test2("world"); 
    cpt1.set_enum_test(msgType::TEST0);
    cpt1.set_bytes_test("42a"); 

    std::cout << "\n=== SHOW SERIALS: === " << std::endl; 
    cpt1.PrintDebugString(); 

    // 2. Write the configuration to file. 
    std::string spt; 
    google::protobuf::TextFormat::PrintToString(cpt1, &spt);
    std::ofstream conf_file; 
    conf_file.open("test.cfg", std::ios::out | std::ios_base::ate);

    if (!conf_file.is_open())
    {
        std::cerr << "Open file test.cfg failed. " << std::endl; 
        return -1; 
    }
    conf_file << spt; 
    conf_file.flush();
    conf_file.close(); 

    std::cout << "\n=== SHOW CONFIGURE FILES: === " << std::endl; 
    system("cat test.cfg"); 

    // 3. Read configuration from file. 
    int fd = open("test.cfg", O_RDONLY); 
    if (fd<0)
    {
        std::cerr << "File test.conf open filed. " << std::endl; 
        return -1; 
    }

    google::protobuf::io::FileInputStream fileInput(fd);
    fileInput.SetCloseOnDelete(true);
    msgType::ProtoTest cpt2; 
    google::protobuf::TextFormat::Parse(&fileInput, &cpt2);
    std::cout << "\n=== SHOW READ SERIALS: === " << std::endl; 
    cpt2.PrintDebugString(); 

    return 0; 
}