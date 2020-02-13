#include <iostream> 
#include <fstream> 
#include <boost/regex.hpp> 

std::string get_container_id(const std::string filename)
{
    std::string container_id {""};  
    std::ifstream cgroup_file; 

    cgroup_file.open(filename, std::ios_base::in); 
    if (!cgroup_file.is_open())
    {
        std::cout << "Error on opening cgroup file: " 
                  << filename << std::endl; 
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
            
            auto docker_pos = suffix.find("docker");
            if ( suffix.length() > docker_pos+70 && \
                docker_pos <= suffix.length())
            {
                container_id = suffix.substr(docker_pos+7, 64);
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
        std::ofstream gcid_file; 
        gcid_file.open("/tmp/gcid.txt", std::ios_base::trunc);
        if (!gcid_file.is_open())
        {
            std::cout << "Failed to log container ID to "
                      << "/tmp/gcid.txt" << std::endl; 
            return 0; 
        }
        else
        {
            gcid_file << docker_id.c_str(); 
            gcid_file.close();
        }    
    }
    else
    {
        std::cout << "Not in a container. " << std::endl; 
    }
}