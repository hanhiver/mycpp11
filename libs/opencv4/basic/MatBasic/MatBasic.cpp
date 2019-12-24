#include <opencv2/opencv.hpp> 
#include <iostream> 
#include <string> 

int main()
{
    std::string filename {"lena.jpg"};
    
    cv::Mat A, C; 
    A = imread(filename, cv::IMREAD_COLOR); 
    cv::Mat B(A);
    C = A; 

    cv::Mat D(A, cv::Rect(10, 10, 100, 100)); 
    cv::Mat E = A(cv::Range::all(), cv::Range(1, 3)); 

    cv::Mat F = A.clone(); 
    cv::Mat G; 
    A.copyTo(G); 

    cv::Mat M(2, 2, CV_8UC3, cv::Scalar(0, 0, 255)); 
    std::cout << "M = " << std::endl << M << std::endl << std::endl; 
}