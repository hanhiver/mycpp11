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
    sys_params.PrintDebugString();

    std::cout << "\nkey_info: " << std::endl;
    key_info.PrintDebugString();
    
    std::cout << "Done. " << std::endl;

    Timer timer;
    // execute task every timer interval
	std::cout << "--- 开始周期定时器 ----" << std::endl;
	timer.start_timer(500, std::bind(func2, "傻X"));
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	timer.stop_timer();
	std::cout << "--- 停止周期定时器 ----" << std::endl;

    // execute task once after delay
	std::cout << "--- 开始一次性定时器 ----" << std::endl;
	timer.start_once(1000, func1);
	std::cout << "--- 停止一次性定时器 ----" << std::endl;

	getchar();
    return 0;
}