#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> 

using std::cin; 
using std::cout; 
using std::endl; 

int main()
{
    double alpha = 0.5; 
    double beta; 
    double input; 

    cv::Mat src1, src2, dst; 
    cout << " Simple Linear Balender " << endl; 
    cout << " Please enter alpha [0.0 ~ 1.0]: " << endl; 
    cin >> input; 

    if (input>=0 && input<=1.0)
    {
        alpha = input; 
    }

    src1 = cv::imread(cv::samples::findFile("LinuxLogo.jpg"));
    src2 = cv::imread(cv::samples::findFile("WindowsLogo.jpg")); 

    if (src1.empty()) { cout << "Error loading src1. " << endl; return EXIT_FAILURE; }
    if (src2.empty()) { cout << "Error loading src2. " << endl; return EXIT_FAILURE; }

    beta = (1.0 - alpha); 
    cv::addWeighted(src1, alpha, src2, beta, 0.0, dst);
    
    cv::imshow("Linear Blend", dst);
    cv::waitKey(0);

    return EXIT_SUCCESS; 
}