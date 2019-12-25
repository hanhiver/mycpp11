#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> 

using std::cin;
using std::cout; 
using std::endl; 
//using namespace cv;


int main(int argc, char** argv)
{
    cv::CommandLineParser parser(argc, argv, "{@input | lena.jpg | input image}");
    cv::Mat image = cv::imread(cv::samples::findFile(parser.get<std::string>("@input")));

    if (image.empty())
    {
        cout << "Error on open or find the image. " << endl; 
        return EXIT_FAILURE;
    }

    cv::Mat new_image = cv::Mat::zeros(image.size(), image.type()); 

    double alpha = 1.0; 
    int beta = 0; 

    cout << " Enter the alpha value [1.0 - 3.0]: " << endl; 
    cin >> alpha; 
    cout << " Enter the beta value [0 - 100]: " << endl; 
    cin >> beta; 

    for (int y=0; y<image.rows; y++)
    {
        for (int x=0; x<image.cols; x++)
        {
            for (int c=0; c<image.channels(); c++)
            {
                new_image.at<cv::Vec3b>(y, x)[c] =
                    cv::saturate_cast<uchar>(alpha*image.at<cv::Vec3b>(y, x)[c] + beta);
            }
        }
    }
    
    cv::imshow("Original Image", image);
    cv::imshow("New Image", new_image);

    cv::waitKey(); 
    return EXIT_SUCCESS;
}
