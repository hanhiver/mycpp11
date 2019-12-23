#include <opencv2/opencv.hpp> 
#include <iostream> 
#include <string> 

int main(int argc, char** argv)
{
    std::string imageName {"lena.jpg"};
    std::string imageGray {"lena_gray.jpg"};

    cv::Mat image; 
    image = imread(imageName, cv::IMREAD_COLOR);

    cv::Mat gray_image; 
    cvtColor(image, gray_image, cv::COLOR_BGR2GRAY); 

    imwrite(imageGray, gray_image);

    return 0;     
}