#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 
#include <iostream> 
#include <fstream> 
#include <string> 

int main(int argc, char** argv)
{
    cv::Mat img_rgb, img_gray, img_cny; 

    cv::namedWindow("in", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("out", cv::WINDOW_AUTOSIZE);

    img_rgb = cv::imread(cv::samples::findFile("lena.jpg"));

    cv::imshow("in", img_rgb); 

    cv::cvtColor(img_rgb, img_gray, cv::COLOR_BGR2GRAY);
    cv::Canny(img_gray, img_cny, 10, 100, 3, true);

    cv::imshow("out", img_cny);
    cv::waitKey(0);

    return EXIT_SUCCESS;
}