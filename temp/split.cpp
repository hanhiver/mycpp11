#include <iostream> 
#include <string> 
#include <algorithm>


int main()
{
    std::string a = "/home/dhan/transfer/images/9965_1_r.jpg";
    std::string filename = std::string(a, a.find_last_of('/')+1, a.length());
    std::cout << "Filename: " << filename << std::endl; 

    std::string pure_name = std::string(filename, 0, filename.find(".jpg"));
    std::cout << "Pure name: " << pure_name << std::endl; 

    size_t dlim_ = pure_name.find('_');
    int frame_idx = std::stoi(std::string(pure_name, 0, dlim_));
    std::string tk_pos_name = std::string(pure_name, dlim_+1);
    int trk_idx = std::stoi(std::string(tk_pos_name, 0, tk_pos_name.find('_')));
    char pos = tk_pos_name[tk_pos_name.length()-1];
    
    std::cout << "Frame Index: " << frame_idx << std::endl; 
    std::cout << "tk_pos_name: " << tk_pos_name << std::endl; 
    std::cout << "Trk Index: " << trk_idx << std::endl; 
    std::cout << "Possion: " << pos << std::endl; 

    return 0;
}