#include <iostream> 
#include <vector> 
#include <chrono>

#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/highgui.hpp> 
#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/cudafeatures2d.hpp>

#include "ThreadPool.h"

using namespace std;

void surf_CPU(cv::Mat& img1, cv::Mat& img2)
{
    cv::Ptr<cv::Feature2D> surf = cv::xfeatures2d::SURF::create(1000);
    
    vector<cv::KeyPoint> keypoints_1, keypoints_2; 
    cv::Mat descriptors_1, descriptors_2; 

    surf->detectAndCompute(img1, cv::Mat(), keypoints_1, descriptors_1); 
    surf->detectAndCompute(img2, cv::Mat(), keypoints_2, descriptors_2); 

    cv::FlannBasedMatcher matcher; 
    std::vector<cv::DMatch> matches; 
    matcher.match(descriptors_1, descriptors_2, matches); 

    std::cout << "#"; 
}

void surf_GPU(cv::Mat& img1, cv::Mat& img2)
{
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
    auto matcher = cv::cuda::DescriptorMatcher::createBFMatcher(cv::NORM_L2);
    vector<cv::DMatch> match_vect; 
    matcher->match(desc1, desc2, match_vect);

    std::cout << "#"; 
}

int main(int argc, char* argv[])
{
    int LOOP = 20; 
    int POOL_SIZE = 4;

    if (argc == 3)
    {
        LOOP = atoi(argv[1]);
        POOL_SIZE = atoi(argv[2]);
    }

    std::cout << "\n=== Test Start === " << std::endl; 
    std::cout << "Total " << LOOP << " tasks, threads pool size: " << POOL_SIZE << std::endl;
    
    cv::Mat img1 = cv::imread("surf_pic1.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread("surf_pic2.jpg", cv::IMREAD_GRAYSCALE); 

    if ((img1.data == NULL) || (img2.data == NULL))
    {
        cout << "Read images failed. " << endl; 
        return -1; 
    }

    ThreadPool tpool(4);
    std::atomic_long num_tasks;

    // === CPU Single thread. 
    std::cout << "\n=== CPU Single thread." << std::endl; 
    auto start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<LOOP; i++)
    {
        surf_CPU(img1, img2);
    }
    auto end = std::chrono::high_resolution_clock::now();

    //auto dur = std::chrono::duration_cast<std::chrono::microseconds> (end - start);
    auto dur = std::chrono::duration<double>(end - start);
    double period = double(dur.count());
    std::cout << "\nsurf_CPU time consumer: " << period << " s. " << std::endl;
    double stand_period = period; 

    // === CPU Multiple threads. 
    std::cout << "\n=== CPU Multiple threads." << std::endl; 
    start = std::chrono::high_resolution_clock::now();
    num_tasks = LOOP;
    for (int i=0; i<LOOP; i++)
    {
        tpool.enqueue([&, i](){
            surf_CPU(img1, img2);
            -- num_tasks;
        });
    }
    while (num_tasks > 0)
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::this_thread::yield();
    }
    end = std::chrono::high_resolution_clock::now();

    //auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    dur = std::chrono::duration<double>(end - start);
    period = double(dur.count());
    std::cout << "\nsurf_CPU MT time consumer: " << period << " s, speed-up ratio: " << stand_period*100/period << "%." << std::endl;

    // === GPU Single thread. 
    std::cout << "\n=== GPU Single thread." << std::endl; 
    start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<LOOP; i++)
    {
        surf_GPU(img1, img2);
    }
    end = std::chrono::high_resolution_clock::now();

    //auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    dur = std::chrono::duration<double>(end - start);
    period = double(dur.count());
    std::cout << "\nsurf_GPU time consumer: " << period << " s, speed-up ratio: " << stand_period*100/period << "%." << std::endl;

    // === GPU Multiple threads. 
    std::cout << "\n=== GPU Multiple threads." << std::endl; 
    start = std::chrono::high_resolution_clock::now();
    num_tasks = LOOP;
    for (int i=0; i<LOOP; i++)
    {
        tpool.enqueue([&, i](){
            surf_GPU(img1, img2);
            -- num_tasks;
        });
    }
    while (num_tasks > 0)
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::this_thread::yield();
    }
    end = std::chrono::high_resolution_clock::now();

    //auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    dur = std::chrono::duration<double>(end - start);
    period = double(dur.count());
    std::cout << "\nsurf_GPU MT time consumer: " << period << " s, speed-up ratio: " << stand_period*100/period << "%." << std::endl;

    std::cout << "\n=== Test Done === " << std::endl; 
    return 0; 
}
