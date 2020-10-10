#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

//include "config.pb.h"
//#include <google/protobuf/text_format.h>
//#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include "params.hpp"
#include "timer.hpp"
#include "sdk_manager.hpp"

int main(int argc, char* argv[])
{
    auto sdk_mgr = SDKManager::Get();
    sdk_mgr.Init("/home/hd275562/myprog/mycpp11/prototype/online_manager_sdk/test.config");
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Main thread Done. " << std::endl;
    sdk_mgr.Shutdown();
}

/*
void func1()
{
	std::cout << "打你怎地！" << std::endl;
}

void func2(std::string x)
{
	std::cout << "你打我呀，" << x << std::endl;
}

int main(int argc, char** argv)
{
    auto params = Params::Get();
    params.ParaseParamsFile("../test.config");

    //auto sys_params = Params::Get().GetSystemParams();
    //auto key_info = Params::Get().GetKeyInfo();
    auto sys_params = params.GetSystemParams();
    auto key_info = params.GetKeyInfo();

    std::cout << "\nsys_params: " << std::endl;
    std::cout << sys_params.server_address() << std::endl;
    sys_params.PrintDebugString();
    int count = sys_params.default_report_call_count();
    std::cout << "call count: " << count << std::endl; 
    std::cout << "\nkey_info: " << std::endl;
    key_info.PrintDebugString();
    
    std::cout << "Done. " << std::endl;

    Timer timer;
    // execute task every timer interval
	std::cout << "--- 开始周期定时器 ----" << std::endl;
	timer.start_timer(100, std::bind(func2, "傻X"));
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	timer.stop_timer();
	std::cout << "--- 停止周期定时器 ----" << std::endl;

    // execute task once after delay
	std::cout << "--- 开始一次性定时器 ----" << std::endl;
	timer.start_once(100, func1);
	std::cout << "--- 停止一次性定时器 ----" << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(150));
    return 0;
}
*/
