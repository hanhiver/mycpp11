#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 
#include <iostream> 
#include <fstream> 
#include <string> 

int main(int argc, char** argv)
{
    cv::Scalar s1(0); 
    std::cout << "s1 = " << s1 << std::endl; 

    cv::Scalar s2(0, 1, 2, 3); 
    std::cout << "s2 = " << s2 << std::endl; 

    cv::Mat a(3, 3, CV_8UC3, cv::Scalar(1, 2, 3, 4)); 
    std::cout << "a = " << a << std::endl; 

    return EXIT_SUCCESS;
}