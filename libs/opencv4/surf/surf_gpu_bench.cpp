#include <iostream> 
#include <vector> 
#include <chrono>
#include <algorithm>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/cudafeatures2d.hpp>

#include "for_each_file.hpp"

using namespace std;

double hist_comp(cv::Mat& img1, cv::Mat& img2)
{
    auto start = std::chrono::high_resolution_clock::now();
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
    if (similarityValue > 0.9)
    {
        std::cout << "Match. " << std::endl;
    }
    else
    {
        std::cout << "Not. " << std::endl;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double period = double(dur.count());
    return period;
}

double surf_GPU(cv::Mat& img1, cv::Mat& img2)
{
    auto start = std::chrono::high_resolution_clock::now();
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

    if (good_matches.size()>4)
    {
        std::cout << "Match." << std::endl;
    }
    else
    {
        std::cout << "Not Match." << std::endl; 
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double period = double(dur.count());

    std::cout << "#"; 
    return period; 
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
    
    auto file_list = get_file_list(std::string(argv[1]));
    
    std::vector<double> time_static; 
    std::vector<cv::Mat> img_queue; 
    int frame = 0; 

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
            continue; 
        }
        else
        {
            frame = frame_idx;
            double time_of_frame = 0.0;
            for (int i=0; i<img_queue.size(); i+=2)
            {
                time_of_frame += hist_comp(img_queue[i], img_queue[i+1]);
                //time_of_frame += surf_GPU(img_queue[i], img_queue[i+1]);
            }
            time_static.push_back(time_of_frame);
            std::cout << "FRAME: " << frame_idx 
                      << ", time: " << time_of_frame 
                      << " us. " << std::endl; 

            img_queue.clear();
            img_queue.push_back(img); 
        }  
    }

    double sum_time = 0; 
    for (auto& item : time_static)
    {
        sum_time += item; 
    }

    std::cout << "Total Time: " << sum_time/1000.0 
              << " ms, average per frame: " << sum_time/time_static.size()/1000.0 
              << " ms." << std::endl; 
    return 0; 
}

#if 0
int main1()
{
    cv::Mat img1 = cv::imread("surf_pic1.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread("surf_pic2.jpg", cv::IMREAD_GRAYSCALE); 

    if ((img1.data == NULL) || (img2.data == NULL))
    {
        cout << "Read images failed. " << endl; 
        return -1; 
    }

    // Use the first GPU devices. 
    cv::cuda::setDevice(0);

    // Create two GPU mat and upload the images. 
    auto start = std::chrono::high_resolution_clock::now();
    cv::cuda::GpuMat gmat1; 
    cv::cuda::GpuMat gmat2;
    gmat1.upload(img1);
    gmat2.upload(img2);
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double period = double(dur.count());
    std::cout << "Create GpuMat and upload images: " << period << " us." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    cv::cuda::SURF_CUDA surf_gpu(1000);

    // Create GpuMat to store the keypoints and relevant descritors. 
    cv::cuda::GpuMat keypt1, keypt2;
    cv::cuda::GpuMat desc1, desc2;

    // Caculate the SURF. 
    surf_gpu(gmat1, cv::cuda::GpuMat(), keypt1, desc1);
    surf_gpu(gmat2, cv::cuda::GpuMat(), keypt2, desc2);

    end = std::chrono::high_resolution_clock::now();
    dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    period = double(dur.count());
    std::cout << "Create and caculate surf: " << period << " us." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    vector<cv::KeyPoint> keypt1_host;
    vector<cv::KeyPoint> keypt2_host;
    surf_gpu.downloadKeypoints(keypt1, keypt1_host);
    surf_gpu.downloadKeypoints(keypt2, keypt2_host);
    end = std::chrono::high_resolution_clock::now();
    dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    period = double(dur.count());
    std::cout << "Download keypoints from GPU: " << period << " us." << std::endl;


    start = std::chrono::high_resolution_clock::now();
    // Create Brute-Force Matcher. 
    auto matcher = cv::cuda::DescriptorMatcher::createBFMatcher(cv::NORM_L2);
    vector<cv::DMatch> match_vect; 
    matcher->match(desc1, desc2, match_vect);
    end = std::chrono::high_resolution_clock::now();
    dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    period = double(dur.count());
    std::cout << "Create and caculate matchs: " << period << " us." << std::endl;

    double max_dist = 0; 
    double min_dist = 100; 

    for (int i=0; i<desc1.rows; i++)
    {
        double dist = match_vect[i].distance;
        if (dist < min_dist) min_dist = dist; 
        if (dist > max_dist) max_dist = dist; 
    }

    cout << "-- Max dist: " << max_dist << endl; 
    cout << "-- Min dist: " << min_dist << endl; 

    vector<cv::DMatch> good_matches;
    for (int i=0; i<desc1.rows; i++)
    {
        if (match_vect[i].distance <= max(2*min_dist, 0.02))
        {
            good_matches.push_back(match_vect[i]);
        }
    }

    for (int i=0; i<(int)good_matches.size(); i++)
    {
        cout << "-- Good Match " << i 
             << " Keypoint 1: " << good_matches[i].queryIdx 
             << " Keypoint 2: " << good_matches[i].trainIdx 
             << endl; 
    }

    return 0; 
}
#endif
