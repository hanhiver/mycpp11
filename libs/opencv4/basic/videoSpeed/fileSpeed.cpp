#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>  

using namespace cv; 
using namespace std;
 
int main(int argc, char** argv)
{
    // Open video file
    VideoCapture video("1s.mp4");
 
    double fps = video.get(CAP_PROP_FPS);
 
    // For OpenCV 3, you can also use the following
    // double fps = video.get(CAP_PROP_FPS);
    cout << "Frames per second using video.get(CV_CAP_PROP_FPS) : " << fps << endl;

    Mat frame; 
    namedWindow("Live", 0);

    while (true)
    {
        video.read(frame);
        if (frame.empty())
        {
            cout << "Video ended. " << endl; 
            break; 
        }
        imshow("Live", frame);
        waitKey(1000); 
    }
     
    video.release(); 
    return 0;
} 
