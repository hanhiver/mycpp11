#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> 

int main(int argc, char** argv)
{
    cv::Mat image, result; 
    float gamma_ = 1.0;

    std::cout << "Please enter the gamma value: " << std::endl; 
    std::cin >> gamma_; 

    image = cv::imread(cv::samples::findFile("lena.jpg"));
    if (image.empty())
    {
        std::cout << "Read Image ERROR. " << std::endl; 
        return EXIT_FAILURE;
    }

    cv::Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for (int i=0; i<256; ++i)
    {
        p[i] = cv::saturate_cast<uchar>(pow(i/255.0, gamma_)*256.0);
    }

    result = image.clone();
    cv::LUT(image, lookUpTable, result); 

    cv::namedWindow("Original"); 
    cv::namedWindow("Gammar Change");

    cv::imshow("Original", image); 
    cv::imshow("Gammar Change", result); 

    cv::waitKey(0);

    return EXIT_SUCCESS;
}