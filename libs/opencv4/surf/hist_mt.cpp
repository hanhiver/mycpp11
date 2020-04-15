#include <iostream> 
#include <vector> 
#include <chrono>

#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/highgui.hpp> 
#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/cudafeatures2d.hpp>
#include <opencv2/imgproc/types_c.h>

#include "ThreadPool.h"

using namespace std;

double hist_comp(cv::Mat& img1, cv::Mat& img2)
{
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
    return similarityValue;
}

int main(int argc, char* argv[])
{
    int LOOP = 300; 
    int POOL_SIZE = 2;

    if (argc == 3)
    {
        LOOP = atoi(argv[1]);
        POOL_SIZE = atoi(argv[2]);
    }

    std::cout << "\n=== Test Start === " << std::endl; 
    std::cout << "Total " << LOOP << " tasks, threads pool size: " << POOL_SIZE << std::endl;
    
    cv::Mat img1 = cv::imread("surf_pic1.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread("surf_pic2.jpg", cv::IMREAD_GRAYSCALE); 
    //cv::Mat img1 = cv::imread("surf_pic1.jpg");
    //cv::Mat img2 = cv::imread("surf_pic2.jpg"); 

    if ((img1.data == NULL) || (img2.data == NULL))
    {
        cout << "Read images failed. " << endl; 
        return -1; 
    }

    ThreadPool tpool(4);
    std::atomic_long num_tasks;

    // === HIST Single thread. 
    std::cout << "\n=== HIST Single thread." << std::endl; 
    auto start = std::chrono::high_resolution_clock::now();
    for (int i=0; i<LOOP; i++)
    {
        hist_comp(img1, img2);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double period = double(dur.count());
    double stand_period = period; 
    std::cout << "\nHIST time consumer: " << period/1000.0 << " ms. " << std::endl;

    // === HIST Multiple threads. 
    std::cout << "\n=== HIST Multiple threads." << std::endl; 
    std::vector<std::future<double>> results; 

    start = std::chrono::high_resolution_clock::now();
    num_tasks = LOOP;
    for (int i=0; i<LOOP; i++)
    {
        results.emplace_back(tpool.enqueue(hist_comp, img1, img2));
    }
    for (auto& item : results)
    {
        item.get();
    }
    end = std::chrono::high_resolution_clock::now();
    dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    period = double(dur.count());
    std::cout << "\nHIST MT time consumer: " << period/1000.0 << " ms, speed-up ratio: " << stand_period*100/period << "%." << std::endl;

    std::cout << "\n=== Test Done === " << std::endl; 
    return 0; 
}
