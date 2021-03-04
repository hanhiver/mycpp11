#include <iostream>
#include <string> 
#include <sstream> 
#include <fstream> 

#include <nlohmann/json.hpp>

std::string read_file(const std::string& filename)
{
	std::ifstream inputFile;
	inputFile.open(filename, std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file: " << filename << std::endl; 
        return "";
    }
	std::ostringstream buf;
	char ch;
	while(buf && inputFile.get(ch))
	{
		buf.put(ch);
	}
	inputFile.close();
	return buf.str();
}

struct JCLASS_sys_params
{
public:
    std::string server_address = "http://vix.aliyun.com/sdk_manager/auth/v1";
    std::string user_name = "default";    
    std::string log_file_root = "/tmp";
    unsigned int log_level = 0;
    unsigned int log_file_max_size = 100;
    unsigned int default_report_call_count = 500;
    unsigned int default_report_countdown_time = 1;
    unsigned int communicate_protocal_version = 1; 

    friend std::ostream& operator<<(std::ostream& os, const JCLASS_sys_params& jclass)
    {
        os << "SYS PARAMS: \n"
           << "===================================================\n"
           << std::boolalpha
           << "server_address: \t\t\t" << jclass.server_address << "\n"
           << "user_name: \t\t\t\t" << jclass.user_name << "\n"
           << "log_file_root: \t\t\t\t" << jclass.log_file_root << "\n"
           << "log_level: \t\t\t\t" << jclass.log_level << "\n"
           << "log_file_max_size: \t\t\t" << jclass.log_file_max_size << "\n"
           << "default_report_call_count: \t\t" << jclass.default_report_call_count << "\n"
           << "default_report_countdown_time: \t\t" << jclass.default_report_countdown_time << "\n"
           << "communicate_protocal_version: \t\t" << jclass.communicate_protocal_version << "\n"
           << "===================================================" << std::endl;
        
        return os;
    }
};

void to_json(nlohmann::json& json, const JCLASS_sys_params& jclass)
{
    json = nlohmann::json{
        {"server_address", jclass.server_address},
        {"user_name", jclass.user_name},
        {"log_file_root", jclass.log_file_root},
        {"log_level", jclass.log_level},
        {"log_file_max_size", jclass.log_file_max_size},
        {"default_report_call_count", jclass.default_report_call_count},
        {"default_report_countdown_time", jclass.default_report_countdown_time},
        {"communicate_protocal_version", jclass.communicate_protocal_version}
    };
}

void from_json(const nlohmann::json& json, JCLASS_sys_params& jclass)
{
    if (json.contains("server_address")) json.at("server_address").get_to(jclass.server_address);
    if (json.contains("user_name")) json.at("user_name").get_to(jclass.user_name);
    if (json.contains("log_file_root")) json.at("log_file_root").get_to(jclass.log_file_root);
    if (json.contains("log_level")) json.at("log_level").get_to(jclass.log_level);
    if (json.contains("log_file_max_size")) json.at("log_file_max_size").get_to(jclass.log_file_max_size);
    if (json.contains("default_report_call_count")) json.at("default_report_call_count").get_to(jclass.default_report_call_count);
    if (json.contains("default_report_countdown_time")) json.at("default_report_countdown_time").get_to(jclass.default_report_countdown_time);
    if (json.contains("communicate_protocal_version")) json.at("communicate_protocal_version").get_to(jclass.communicate_protocal_version);
}

struct JCLASS_debug_options
{
public:
    bool log_also_log_stderr = false;
    bool log_redirect_stderr = false;
    unsigned int log_stderr_threshold = 2;
    bool update_server_until_millisecond = false;

    friend std::ostream& operator<<(std::ostream& os, const JCLASS_debug_options& jclass)
    {
        os << "DEBUG OPTIONS: \n"
           << "===================================================\n"
           << std::boolalpha
           << "log_also_log_stderr: \t\t\t" << jclass.log_also_log_stderr << "\n"
           << "log_redirect_stderr: \t\t\t" << jclass.log_redirect_stderr << "\n"
           << "log_stderr_threshold: \t\t\t" << jclass.log_stderr_threshold << "\n"
           << "update_server_until_millisecond: \t" << jclass.update_server_until_millisecond << "\n"
           << "===================================================" << std::endl;
        
        return os;
    }
};

void to_json(nlohmann::json& json, const JCLASS_debug_options& jclass)
{
    json = nlohmann::json{
        {"log_also_log_stderr", jclass.log_also_log_stderr},
        {"log_redirect_stderr", jclass.log_redirect_stderr},
        {"log_stderr_threshold", jclass.log_stderr_threshold},
        {"update_server_until_millisecond", jclass.update_server_until_millisecond}
    };
}

void from_json(const nlohmann::json& json, JCLASS_debug_options& jclass)
{
    if (json.contains("log_also_log_stderr")) json.at("log_also_log_stderr").get_to(jclass.log_also_log_stderr);
    if (json.contains("log_redirect_stderr")) json.at("log_redirect_stderr").get_to(jclass.log_redirect_stderr);
    if (json.contains("log_stderr_threshold")) json.at("log_stderr_threshold").get_to(jclass.log_stderr_threshold);
    if (json.contains("update_server_until_millisecond")) json.at("update_server_until_millisecond").get_to(jclass.update_server_until_millisecond);
}


int main(int argc, char *argv[])
{
    nlohmann::json j; 
    std::string json_str = read_file("../test.json");

    try
    {
        j = nlohmann::json::parse(json_str.c_str());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << j.dump(4) << std::endl; 

    JCLASS_debug_options debug_options;
    JCLASS_sys_params sys_params;

    if (j.contains("debug_options"))
    {
        JCLASS_debug_options debug_options = j.at("debug_options").get<JCLASS_debug_options>();
        std::cout << debug_options << std::endl; 
    }

    if (j.contains("sys_params"))
    {
        JCLASS_sys_params sys_params = j.at("sys_params").get<JCLASS_sys_params>();
        std::cout << sys_params << std::endl; 
    }

    //std::cout << "DEBUG OPTIONS: \n" << debug_option << std::endl; 
    //std::cout << "SYS PARAMS: \n" << sys_params << std::endl; 

    nlohmann::json j2;
    j2["sys_params"] = sys_params; 
    std::cout << j2.dump(4) << std::endl; 

    return 0;
}