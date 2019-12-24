#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 
#include <iostream> 
#include <string> 

void Sharpen(const cv::Mat& myImage, cv::Mat& result);

int main(int argc, char** argv)
{
    std::string filename {"../../RES/lena.jpg"};

    cv::Mat src, dst0, dst1; 
    src = cv::imread(filename, cv::IMREAD_COLOR); 

    if (src.empty())
    {
        std::cerr << "Failed to open the file: " << filename << std::endl; 
        return EXIT_FAILURE; 
    }
    cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);

    cv::imshow("Input", src); 

    double t = (double)cv::getTickCount(); 
    Sharpen(src, dst0); 
    t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();

    std::cout << "hand written function time: " << t << " seconds. " << std::endl; 
    cv::imshow("Output", dst0); 

    cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1,  0, 
                                             -1,  5, -1,
                                              0, -1,  0); 
    
    t = ((double)cv::getTickCount()); 
    cv::filter2D(src, dst1, src.depth(), kernel); 
    t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();

    std::cout << "Build-in filter2D time:     " << t << " seconds. " << std::endl; 
    cv::imshow("Output", dst1); 

    cv::waitKey(); 
    return EXIT_SUCCESS; 
}

void Sharpen(const cv::Mat& myImage, cv::Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U); 

    
    const int nChannels = myImage.channels(); 
    Result.create(myImage.size(), myImage.type());
    
    for (int j=1; j<myImage.rows-1; ++j)
    {
        const uchar* pre = myImage.ptr<uchar>(j -1); 
        const uchar* cur = myImage.ptr<uchar>(j); 
        const uchar* nxt = myImage.ptr<uchar>(j + 1);

        uchar* output = Result.ptr<uchar>(j); 

        for (int i=nChannels; i<nChannels*(myImage.cols-1); ++i)
        {
            *output++ = cv::saturate_cast<uchar>(5*cur[i]
                         - cur[i-nChannels] - cur[i+nChannels] 
                         - pre[i] - nxt[i]); 
        }
    } 
    
    Result.row(0).setTo(cv::Scalar(0));
    Result.row(Result.rows-1).setTo(cv::Scalar(0));
    Result.col(0).setTo(cv::Scalar(0));
    Result.col(Result.cols-1).setTo(cv::Scalar(0));
}