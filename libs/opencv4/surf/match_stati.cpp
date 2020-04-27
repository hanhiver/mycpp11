#include <iostream> 
#include <vector> 
#include <chrono>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath> 

#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/cudafeatures2d.hpp>

#include "for_each_file.hpp"
#include "ThreadPool.h"

using namespace std;

int POOL_SIZE = 4; 

double HIST_MATCH_RATE = 0.95;
double COMB_RECHECK_RATE = 0.95;
bool SHOW_UNMATCHS = false;

double hist_comp(cv::Mat& img1, cv::Mat& img2)
{
    //auto start = std::chrono::high_resolution_clock::now();
    cv::Mat img1c; 
    cv::Mat img2c;
    cvtColor(img1, img1c, cv::COLOR_GRAY2RGB);
    cvtColor(img2, img2c, cv::COLOR_GRAY2RGB);
    int hBins = 256, sBins = 256;
	int histSize[] = { hBins, sBins };
	//H:0~180, S:0~255,V:0~255
	//H色调取值范围
	float hRanges[] = { 0, 180 };
	//S饱和度取值范围
	float sRanges[] = { 0, 255 };
	const float* ranges[] = { hRanges, sRanges };
	int channels[] = { 0, 1 };//二维直方图
	cv::MatND hist1, hist2;
    cv::calcHist(&img1c, 1, channels, cv::Mat(), hist1, 2, histSize, ranges, true, false);
	cv::normalize(hist1, hist1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	cv::calcHist(&img2c, 1, channels, cv::Mat(), hist2, 2, histSize, ranges, true, false);
	cv::normalize(hist2, hist2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	//double similarityValue = compareHist(hist1, hist2, cv::CV_COMP_CORREL);
    double similarityValue = compareHist(hist1, hist2, cv::HISTCMP_CORREL);
    //std::cout << "Similarity: " << similarityValue << std::endl; 
    
    //auto end = std::chrono::high_resolution_clock::now();
    //auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    //double period = double(dur.count());

    //return similarityValue;
    
    if (similarityValue > HIST_MATCH_RATE)
    {
        return (similarityValue - HIST_MATCH_RATE)*19;
    }
    else
    {
        return 0.0;
    }
}

double surf_GPU(cv::Mat& img1, cv::Mat& img2)
{
    //auto start = std::chrono::high_resolution_clock::now();
    // Create two GPU mat and upload the images. 
    cv::cuda::GpuMat gmat1; 
    cv::cuda::GpuMat gmat2;
    gmat1.upload(img1);
    gmat2.upload(img2);

    cv::cuda::SURF_CUDA surf_gpu(1000);

    // Create GpuMat to store the keypoints and relevant descritors. 
    cv::cuda::GpuMat keypt1, keypt2;
    cv::cuda::GpuMat desc1, desc2;

    // Caculate the SURF. 
    surf_gpu(gmat1, cv::cuda::GpuMat(), keypt1, desc1);
    surf_gpu(gmat2, cv::cuda::GpuMat(), keypt2, desc2);

    vector<cv::KeyPoint> keypt1_host;
    vector<cv::KeyPoint> keypt2_host;
    surf_gpu.downloadKeypoints(keypt1, keypt1_host);
    surf_gpu.downloadKeypoints(keypt2, keypt2_host);

    // Create Brute-Force Matcher. 
    //auto matcher = cv::cuda::DescriptorMatcher::createBFMatcher(cv::NORM_L2);
    auto matcher = cv::cuda::DescriptorMatcher::createBFMatcher(surf_gpu.defaultNorm());
    
    vector< vector<cv::DMatch> > match_vect; 
    //matcher->match(desc1, desc2, match_vect);
    matcher->knnMatch(desc1, desc2, match_vect, 2);

    vector<cv::DMatch> good_matches;
    for(auto& match : match_vect)
    {
        if (match[0].distance < 0.7*match[1].distance)
        {
            good_matches.push_back(match[0]);
        }
    }
    
    //auto end = std::chrono::high_resolution_clock::now();
    //auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    //double period = double(dur.count());

    if (good_matches.size()>4)
    {
        //std::cout << static_cast<double>(good_matches.size())/std::min(img1.total(), img2.total()) << std::endl;
        //return static_cast<double>(good_matches.size())/std::min(img1.total(), img2.total());
        return std::log(good_matches.size())/std::log(match_vect.size());
        //return std::log(good_matches.size())/std::log(img1.total());
    }
    else
    {
        return 0.0; 
    }
}

double combine(cv::Mat img1, cv::Mat img2)
{
    double hist_res = hist_comp(img1, img2);
    if (hist_res == 0.0)
    {
        //std::cout << "Recheck. " << std::endl; 
        double surf_res = surf_GPU(img1, img2);
        return surf_res; 
    }
    else
    {
        return hist_res; 
    }
}

void phase_filename(std::string& fullpath, int* frame_idx, int* trk_idx, char* pos)
{
    std::string filename = std::string(fullpath, fullpath.find_last_of('/')+1, fullpath.length());
    std::string pure_name = std::string(filename, 0, filename.find(".jpg"));

    size_t dlim_ = pure_name.find('_');
    *frame_idx = std::stoi(std::string(pure_name, 0, dlim_));
    std::string tk_pos_name = std::string(pure_name, dlim_+1);

    dlim_ = tk_pos_name.find('_');
    *trk_idx = std::stoi(std::string(tk_pos_name, 0, dlim_));
    *pos = tk_pos_name[dlim_];

    return; 
}

std::vector<std::string> get_file_list(std::string folder)
{
    auto file_list = ls(folder, false);

    struct 
    {
        bool operator()(std::string& a, std::string& b)
        {
            int frame_idx_a, frame_idx_b;
            int trk_idx_a, trk_idx_b; 
            char pos_a, pos_b;

            phase_filename(a, &frame_idx_a, &trk_idx_a, &pos_a);
            phase_filename(b, &frame_idx_b, &trk_idx_b, &pos_b);

            if (frame_idx_a < frame_idx_b)
            {
                return true; 
            }
            else if (frame_idx_a > frame_idx_b)
            {
                return false;
            }
            else
            {
                if (trk_idx_a < trk_idx_b)
                {
                    return true;
                }
                else if(trk_idx_a > trk_idx_b)
                {
                    return false;
                }
                else
                {
                    if (pos_a > pos_b)
                    {
                        return true;
                    }
                    else
                    {
                        return false; 
                    }
                    
                }
                
            }
        }
    } filename_less;

    std::sort(file_list.begin(), file_list.end(), filename_less);

    return file_list; 
}


int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cout << "Usage: " << argv[0] << " <folder of the images> [output csv file]." << std::endl; 
        exit(-1);
    }

    std::cout << "Folder: " << argv[1] << std::endl; 
    
    std::ofstream csv_file;
    if (argc == 3)
    {
        std::cout << "Csv File: " << argv[2] << std::endl;
        // Open the csv file to save all compare results. 
        csv_file.open(argv[2]);
        if (!csv_file.is_open())
        {
            std::cerr << "Failed to open: " << argv[2] << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
    auto file_list = get_file_list(std::string(argv[1]));
    int num_files = static_cast<int>(file_list.size());

    //std::array<double, num_files/2> matches_rates_surf; 
    double* matches_rates_surf = new double[num_files/2]();
    std::vector<double> time_static; 

    std::vector<std::string> imgs_name;
    std::vector<cv::Mat> img_queue; 
    std::vector<int> img_idx_queue;
    int frame = 0; 

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double period = double(dur.count());

    ThreadPool tpool(POOL_SIZE);

    // === SURF ===
    //std::cout << "=== SURF ===" << std::endl; 
    for (int i=0; i<num_files; i++)
    {
        //std::cout << item << std::endl; 
        int frame_idx;
        int trk_idx; 
        char pos;
        
        phase_filename(file_list[i], &frame_idx, &trk_idx, &pos); 
        cv::Mat img = cv::imread(file_list[i], cv::IMREAD_GRAYSCALE);
        
        if (frame == frame_idx)
        {
            // 如果是同一帧画面。
            img_queue.push_back(img); 
            img_idx_queue.push_back(i);
            imgs_name.push_back(file_list[i]);
            continue; 
        }
        else
        {
            start = std::chrono::high_resolution_clock::now();
            frame = frame_idx;
            for (int j=0; j<img_queue.size(); j+=2)
            {
                double res = surf_GPU(img_queue[j], img_queue[j+1]);
                matches_rates_surf[img_idx_queue[j]/2] = res;
            }
            end = std::chrono::high_resolution_clock::now();
            dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            period = double(dur.count());
            time_static.push_back(period);

            img_idx_queue.clear();
            img_idx_queue.push_back(i);
            img_queue.clear();
            img_queue.push_back(img); 
            imgs_name.clear();
            imgs_name.push_back(file_list[i]);
        }  
    }

    double sum_match_rate = 0; 
    //for (auto& item : matches_rates_surf)
    for (int i=0; i<num_files/2; i++)
    {
        sum_match_rate += matches_rates_surf[i]; 
    }
    std::cout << "SURF total match rate: " 
              << double(sum_match_rate)/double(num_files/2)*100.0
              << "%, "; 

    double sum_match_time = 0;
    for (auto& item : time_static)
    {
        sum_match_time += item; 
    }
    std::cout << "total time: " << sum_match_time/1000.0/1000.0 << " s, "
              << "avg per frame: " << sum_match_time/double(time_static.size()) << " us. "
              << std::endl; 

    //match_rates.clear();
    time_static.clear();
    img_idx_queue.clear();
    img_queue.clear();
    imgs_name.clear();
    
    // === HIST ===
    //std::cout << "=== HIST ===" << std::endl; 
    std::vector<std::future<double>> results; 
    double* matches_rates_hist = new double[num_files/2]();

    for (int i=0; i<num_files; i++)
    {
        //std::cout << item << std::endl; 
        int frame_idx;
        int trk_idx; 
        char pos;
        
        phase_filename(file_list[i], &frame_idx, &trk_idx, &pos); 
        cv::Mat img = cv::imread(file_list[i], cv::IMREAD_GRAYSCALE);
        
        if (frame == frame_idx)
        {
            // 如果是同一帧画面。
            img_queue.push_back(img); 
            img_idx_queue.push_back(i);
            imgs_name.push_back(file_list[i]);
            continue; 
        }
        else
        {
            frame = frame_idx;
            results.clear();

            start = std::chrono::high_resolution_clock::now();
            for (int j=0; j<img_queue.size(); j+=2)
            {
                results.emplace_back(tpool.enqueue(hist_comp, img_queue[j], img_queue[j+1]));
            }

            for (int k=0; k<results.size(); ++k)
            {
                double res = results[k].get();
                matches_rates_hist[img_idx_queue[k*2]/2] = res;
                if (res == 0)
                {
                    matches_rates_hist[img_idx_queue[k*2]/2] = 0.0;
                    if (SHOW_UNMATCHS)
                    {
                        std::cout << "NOT match: " << res << ", " << imgs_name[2*i] 
                              << " & " << imgs_name[2*i+1] << std::endl;
                    }
                }
            }

            end = std::chrono::high_resolution_clock::now();
            dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            period = double(dur.count());
            time_static.push_back(period);

            img_idx_queue.clear();
            img_idx_queue.push_back(i);
            img_queue.clear();
            img_queue.push_back(img); 
            imgs_name.clear();
            imgs_name.push_back(file_list[i]);
        }  
    }

    sum_match_rate = 0; 
    for (int i=0; i<num_files/2; i++)
    {
        sum_match_rate += matches_rates_hist[i]; 
    }
    std::cout << "HIST total match rate: " 
              << double(sum_match_rate)/double(num_files/2)*100.0
              << "%, "; 

    sum_match_time = 0;
    for (auto& item : time_static)
    {
        sum_match_time += item; 
    }
    std::cout << "total time: " << sum_match_time/1000.0/1000.0 << " s, "
              << "avg per frame: " << sum_match_time/double(time_static.size()) << " us. "
              << std::endl; 

    time_static.clear();
    img_idx_queue.clear();
    img_queue.clear();
    imgs_name.clear();

    // === COMB ===
    //std::cout << "=== COMB ===" << std::endl; 
    double* matches_rates_comb = new double[num_files/2]();
    for (int i=0; i<num_files; i++)
    {
        //std::cout << item << std::endl; 
        int frame_idx;
        int trk_idx; 
        char pos;
        
        phase_filename(file_list[i], &frame_idx, &trk_idx, &pos); 
        cv::Mat img = cv::imread(file_list[i], cv::IMREAD_GRAYSCALE);
        
        if (frame == frame_idx)
        {
            // 如果是同一帧画面。
            img_queue.push_back(img); 
            img_idx_queue.push_back(i);
            imgs_name.push_back(file_list[i]);
            continue; 
        }
        else
        {
            frame = frame_idx;
            results.clear();

            start = std::chrono::high_resolution_clock::now();
            for (int j=0; j<img_queue.size(); j+=2)
            {
                results.emplace_back(tpool.enqueue(combine, img_queue[j], img_queue[j+1]));
            }

            for (int k=0; k<results.size(); ++k)
            {
                double res = results[k].get();
                matches_rates_comb[img_idx_queue[k*2]/2] = res;
                if (res < HIST_MATCH_RATE)
                {
                    if (SHOW_UNMATCHS)
                    {
                        std::cout << "NOT match: " << res << ", " << imgs_name[2*i] 
                              << " & " << imgs_name[2*i+1] << std::endl;
                    }
                }
            }
            
            end = std::chrono::high_resolution_clock::now();
            dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            period = double(dur.count());
            time_static.push_back(period);

            img_idx_queue.clear();
            img_idx_queue.push_back(i);
            img_queue.clear();
            img_queue.push_back(img); 
            imgs_name.clear();
            imgs_name.push_back(file_list[i]);
        }  
    }

    sum_match_rate = 0; 
    for (int i=0; i<num_files/2; i++)
    {
        sum_match_rate += matches_rates_comb[i]; 
    }
    std::cout << "COMB total match rate: " 
              << double(sum_match_rate)/double(num_files/2)*100.0
              << "%, "; 

    sum_match_time = 0;
    for (auto& item : time_static)
    {
        sum_match_time += item; 
    }
    std::cout << "total time: " << sum_match_time/1000.0/1000.0 << " s, "
              << "avg per frame: " << sum_match_time/double(time_static.size()) << " us. "
              << std::endl; 

    time_static.clear();
    img_idx_queue.clear();
    img_queue.clear();
    imgs_name.clear();
    std::cout << std::endl;
    
    // === Save output csv file === //
    if (argc == 3)
    {
        csv_file << "index, img1, img2, SURF, HIST, COMB\n";
        for (int i=0; i<num_files; i+=2)
        {
            csv_file << std::to_string(i) << ", "
                    << file_list[i] << ", " << file_list[i+1] << ", ";
            std::ostringstream double_string;
            double_string.precision(15);
            double_string << matches_rates_surf[i/2] << ", " 
                        << matches_rates_hist[i/2] << ", "
                        << matches_rates_comb[i/2];
            csv_file << double_string.str() << "\n";
        }
        csv_file.close();
    }
    else
    {
        std::cout << "num, SURF, HIST, COMB\n";
        for (int i=0; i<num_files; i+=2)
        {
            std::cout << std::to_string(i) << ", "
                      << matches_rates_surf[i/2] << ", " 
                      << matches_rates_hist[i/2] << ", "
                      << matches_rates_comb[i/2] << std::endl;
        }
    }
    

    return 0; 
}
