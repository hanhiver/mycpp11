#include <iostream> 
#include <fstream> 
//#include <boost/regex.hpp> 

/*
std::string get_container_id1(const std::string filename)
{
    std::string container_id {""};  

    std::ifstream cgroup_file; 
    //std::string cgroup_file_name = "/proc/1/cgroup";
    std::string cgroup_file_name = filename;

    cgroup_file.open(filename, std::ios_base::in); 
    if (!cgroup_file.is_open())
    {
        std::cout << "Error on opening cgroup file: " 
                  << cgroup_file_name << std::endl; 
        return container_id;
    }

    auto cgroup_line1_reg = boost::regex("1:name=systemd:/"); 
    boost::smatch match;  

    std::string line;
    while (std::getline(cgroup_file, line))
    {
        if (boost::regex_search(line, match, cgroup_line1_reg))
        {
            std::string suffix(match.suffix().str()); 
            std::cout << suffix << std::endl; 
            
            auto docker_pos = suffix.find("docker");
            std::cout << "suffix length: " << suffix.length() 
                      << " docker_pos: " << docker_pos << std::endl; 

            if ( suffix.length() > docker_pos+70 && \
                docker_pos <= suffix.length())
            {
                container_id = suffix.substr(docker_pos+7, 64);
                
                std::cout << "In a container. " << std::endl; 
                std::cout << docker_pos << std::endl; 
                std::cout << container_id << std::endl;
                
            }
        }
    }

    cgroup_file.clear();
    cgroup_file.close();

    return container_id; 
}
*/

std::string get_container_id(const std::string filename)
{
    std::string container_id {""};  

    std::ifstream cgroup_file; 
    //std::string cgroup_file_name = "/proc/1/cgroup";
    std::string cgroup_file_name = filename;

    cgroup_file.open(filename); 
    if (!cgroup_file.is_open())
    {
        std::cout << "Error opening cgroup file: " 
                  << cgroup_file_name << std::endl; 
        return container_id;
    }

    std::string cgroup_line1 {"1:name=systemd:/"}; 

    std::string line;
    while (std::getline(cgroup_file, line))
    {
        if (line.substr(0, 16) == cgroup_line1)
        {
            std::string suffix = line.substr(16);  
            std::cout << suffix << std::endl; 
            
            auto docker_pos = suffix.find("docker");
            /*
            std::cout << "suffix length: " << suffix.length() 
                        << " docker_pos: " << docker_pos << std::endl; 
            */

            if (docker_pos <= suffix.length())
            {
                container_id = suffix.substr(docker_pos+7, 64);
                std::cout << "In a container. " << std::endl; 
                std::cout << "Docker ps: " << docker_pos << std::endl; 
                std::cout << "Docker ID: " << container_id << std::endl;
            }
        }
    }

    cgroup_file.clear();
    cgroup_file.close();

    return container_id; 
}


int main(int argc, char* argv[])
{
    std::string docker_id; 
    if (argc > 1)
    {
        docker_id = get_container_id(argv[1]);
    }
    else
    {
        docker_id = get_container_id("/proc/1/cgroup"); 
    }
    
    if (!docker_id.empty())
    {
        std::cout << "In a container, ID: " 
                  << docker_id << std::endl;
    }
    else
    {
        std::cout << "Not in a container. " << std::endl; 
    }
}