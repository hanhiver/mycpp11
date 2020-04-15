#include <iostream> 
#include <vector> 
#include <chrono>
#include <algorithm>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/cudafeatures2d.hpp>

#include "for_each_file.hpp"
#include "ThreadPool.h"

using namespace std;

int POOL_SIZE = 2; 

double HIST_MATCH_RATE = 0.9;
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

    return similarityValue;
    /*
    if (similarityValue > 0.90)
    {
        return 1;
    }
    else
    {
        return 0.0;
    }*/
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
        return 1.0;
    }
    else
    {
        return 0.0; 
    }
}

double combine(cv::Mat img1, cv::Mat img2)
{
    double res = hist_comp(img1, img2);
    if (res < COMB_RECHECK_RATE)
    {
        //std::cout << "Recheck. " << std::endl; 
        res = surf_GPU(img1, img2);
    }

    return res; 
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
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <folder of the images>." << std::endl; 
        exit(-1);
    }

    std::cout << argv[1] << std::endl; 
    
    auto file_list = get_file_list(std::string(argv[1]));
    
    std::vector<double> match_rates; 
    std::vector<double> time_static; 

    std::vector<std::string> imgs_name;
    std::vector<cv::Mat> img_queue; 
    int frame = 0; 

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double period = double(dur.count());

    ThreadPool tpool(POOL_SIZE);

    // === SURF ===
    //std::cout << "=== SURF ===" << std::endl; 
    for (auto& item : file_list)
    {
        //std::cout << item << std::endl; 
        int frame_idx;
        int trk_idx; 
        char pos;
        
        phase_filename(item, &frame_idx, &trk_idx, &pos); 
        cv::Mat img = cv::imread(item, cv::IMREAD_GRAYSCALE);
        
        if (frame == frame_idx)
        {
            // 如果是同一帧画面。
            img_queue.push_back(img); 
            imgs_name.push_back(item);
            continue; 
        }
        else
        {
            start = std::chrono::high_resolution_clock::now();
            frame = frame_idx;
            for (int i=0; i<img_queue.size(); i+=2)
            {
                double res = surf_GPU(img_queue[i], img_queue[i+1]);
                match_rates.push_back(res);
                if (res < 0.9)
                {
                    if (SHOW_UNMATCHS)
                    {
                        std::cout << "NOT match: " << res << ", " << imgs_name[i] 
                              << " & " << imgs_name[i+1] << std::endl;
                    }
                }
            }
            end = std::chrono::high_resolution_clock::now();
            dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            period = double(dur.count());
            time_static.push_back(period);

            img_queue.clear();
            img_queue.push_back(img); 
            imgs_name.clear();
            imgs_name.push_back(item);
        }  
    }

    double sum_match_rate = 0; 
    for (auto& item : match_rates)
    {
        sum_match_rate += item; 
    }
    std::cout << "SURF total match rate: " 
              << double(sum_match_rate)/double(match_rates.size())*100.0
              << "%, "; 

    double sum_match_time = 0;
    for (auto& item : time_static)
    {
        sum_match_time += item; 
    }
    std::cout << "total time: " << sum_match_time/1000.0/1000.0 << " s, "
              << "avg per frame: " << sum_match_time/double(time_static.size()) << " us. "
              << std::endl; 

    match_rates.clear();
    time_static.clear();
    img_queue.clear();
    imgs_name.clear();
    
    // === HIST ===
    //std::cout << "=== HIST ===" << std::endl; 
    std::vector<std::future<double>> results; 
    for (auto& item : file_list)
    {
        //std::cout << item << std::endl; 
        int frame_idx;
        int trk_idx; 
        char pos;
        
        phase_filename(item, &frame_idx, &trk_idx, &pos); 
        cv::Mat img = cv::imread(item, cv::IMREAD_GRAYSCALE);
        
        if (frame == frame_idx)
        {
            // 如果是同一帧画面。
            img_queue.push_back(img); 
            imgs_name.push_back(item);
            continue; 
        }
        else
        {
            frame = frame_idx;
            results.clear();

            start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<img_queue.size(); i+=2)
            {
                results.emplace_back(tpool.enqueue(hist_comp, img_queue[i], img_queue[i+1]));
            }

            for (int i=0; i<results.size(); ++i)
            {
                double res = results[i].get();
                if (res < HIST_MATCH_RATE)
                {
                    match_rates.push_back(0.0);
                    if (SHOW_UNMATCHS)
                    {
                        std::cout << "NOT match: " << res << ", " << imgs_name[2*i] 
                              << " & " << imgs_name[2*i+1] << std::endl;
                    }
                }
                else
                {
                    match_rates.push_back(1);
                }
            }

            end = std::chrono::high_resolution_clock::now();
            dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            period = double(dur.count());
            time_static.push_back(period);

            img_queue.clear();
            img_queue.push_back(img); 
            imgs_name.clear();
            imgs_name.push_back(item);
        }  
    }

    sum_match_rate = 0; 
    for (auto& item : match_rates)
    {
        sum_match_rate += item; 
    }
    std::cout << "HIST total match rate: " 
              << double(sum_match_rate)/double(match_rates.size())*100.0
              << "%, "; 

    sum_match_time = 0;
    for (auto& item : time_static)
    {
        sum_match_time += item; 
    }
    std::cout << "total time: " << sum_match_time/1000.0/1000.0 << " s, "
              << "avg per frame: " << sum_match_time/double(time_static.size()) << " us. "
              << std::endl; 

    match_rates.clear();
    time_static.clear();
    img_queue.clear();
    imgs_name.clear();

    // === COMB ===
    //std::cout << "=== COMB ===" << std::endl; 
    for (auto& item : file_list)
    {
        //std::cout << item << std::endl; 
        int frame_idx;
        int trk_idx; 
        char pos;
        
        phase_filename(item, &frame_idx, &trk_idx, &pos); 
        cv::Mat img = cv::imread(item, cv::IMREAD_GRAYSCALE);
        
        if (frame == frame_idx)
        {
            // 如果是同一帧画面。
            img_queue.push_back(img); 
            imgs_name.push_back(item);
            continue; 
        }
        else
        {
            results.clear();

            start = std::chrono::high_resolution_clock::now();
            frame = frame_idx;
            for (int i=0; i<img_queue.size(); i+=2)
            {
                results.emplace_back(tpool.enqueue(combine, img_queue[i], img_queue[i+1]));
            }

            for (int i=0; i<results.size(); ++i)
            {
                double res = results[i].get();
                if (res < HIST_MATCH_RATE)
                {
                    match_rates.push_back(0.0);
                    if (SHOW_UNMATCHS)
                    {
                        std::cout << "NOT match: " << res << ", " << imgs_name[2*i] 
                              << " & " << imgs_name[2*i+1] << std::endl;
                    }
                }
                else
                {
                    match_rates.push_back(1);
                }
            }
            
            end = std::chrono::high_resolution_clock::now();
            dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            period = double(dur.count());
            time_static.push_back(period);

            img_queue.clear();
            img_queue.push_back(img); 
            imgs_name.clear();
            imgs_name.push_back(item);
        }  
    }

    sum_match_rate = 0; 
    for (auto& item : match_rates)
    {
        sum_match_rate += item; 
    }
    std::cout << "COMB total match rate: " 
              << double(sum_match_rate)/double(match_rates.size())*100.0
              << "%, "; 

    sum_match_time = 0;
    for (auto& item : time_static)
    {
        sum_match_time += item; 
    }
    std::cout << "total time: " << sum_match_time/1000.0/1000.0 << " s, "
              << "avg per frame: " << sum_match_time/double(time_static.size()) << " us. "
              << std::endl; 

    match_rates.clear();
    time_static.clear();
    img_queue.clear();
    imgs_name.clear();
    std::cout << std::endl;
    return 0; 
}
