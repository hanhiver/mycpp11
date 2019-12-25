#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> 

using std::cin;
using std::cout; 
using std::endl; 
//using namespace cv;

/*
int main( int argc, char** argv )
{
    /// Read image given by user
    //! [basic-linear-transform-load]
    CommandLineParser parser( argc, argv, "{@input | lena.jpg | input image}" );
    Mat image = imread( samples::findFile( parser.get<String>( "@input" ) ) );
    if( image.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }
    //! [basic-linear-transform-load]

    //! [basic-linear-transform-output]
    Mat new_image = Mat::zeros( image.size(), image.type() );
    //! [basic-linear-transform-output]

    //! [basic-linear-transform-parameters]
    double alpha = 1.0; 
    int beta = 0;       

    /// Initialize values
    cout << " Basic Linear Transforms " << endl;
    cout << "-------------------------" << endl;
    cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
    cout << "* Enter the beta value [0-100]: ";    cin >> beta;
    //! [basic-linear-transform-parameters]

    /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
    /// Instead of these 'for' loops we could have used simply:
    /// image.convertTo(new_image, -1, alpha, beta);
    /// but we wanted to show you how to access the pixels :)
    //! [basic-linear-transform-operation]
    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < image.channels(); c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>( alpha*image.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }
    //! [basic-linear-transform-operation]

    //! [basic-linear-transform-display]
    /// Show stuff
    imshow("Original Image", image);
    imshow("New Image", new_image);

    /// Wait until the user press a key
    waitKey();
    //! [basic-linear-transform-display]
    return 0;
}
*/

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
