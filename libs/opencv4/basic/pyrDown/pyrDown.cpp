#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 
#include <iostream> 
#include <fstream> 
#include <string> 

int main(int argc, char** argv)
{
    cv::Mat img1, img2; 

    cv::namedWindow("in", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("out", cv::WINDOW_AUTOSIZE);

    img1 = cv::imread(cv::samples::findFile("lena.jpg"));

    cv::imshow("in", img1); 
    cv::pyrDown(img1, img2); 

    cv::imshow("out", img2);
    cv::waitKey(0);

    return EXIT_SUCCESS;
}