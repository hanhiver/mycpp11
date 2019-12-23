#include <iostream> 
#include <vector> 
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/highgui.hpp> 

using namespace cv; 
using namespace std; 

int main()
{
    Mat img1 = imread("surf_pic1.jpg", 1);
    Mat img2 = imread("surf_pic2.jpg", 1); 

    if ((img1.data == NULL) || (img2.data == NULL))
    {
        cout << "Read images failed. " << endl; 
        return -1; 
    }

    Ptr<Feature2D> surf = xfeatures2d::SURF::create(1000);
    
    vector<KeyPoint> keypoints_1, keypoints_2; 
    Mat descriptors_1, descriptors_2; 

    surf->detectAndCompute(img1, Mat(), keypoints_1, descriptors_1); 
    surf->detectAndCompute(img2, Mat(), keypoints_2, descriptors_2); 
    drawKeypoints(img1, keypoints_1, img1); 
    drawKeypoints(img2, keypoints_2, img2); 

    /*
    namedWindow("img1", 0);
    resizeWindow("img1", 500, 500); 
    imshow("img1", img1); 

    namedWindow("img2", 0);
    resizeWindow("img2", 500, 500); 
    imshow("img2", img2); 
    */

    FlannBasedMatcher matcher; 
    std::vector<DMatch> matches; 
    matcher.match(descriptors_1, descriptors_2, matches); 
    double max_dist = 0; 
    double min_dist = 100; 

    for (int i=0; i<descriptors_1.rows; i++)
    {
        double dist = matches[i].distance; 
        if (dist<min_dist) min_dist = dist; 
        if (dist>max_dist) max_dist = dist; 
    }

    cout << "-- Max dist: " << max_dist << endl; 
    cout << "-- Min dist: " << min_dist << endl; 

    std::vector<DMatch> good_matches; 
    for (int i=0; i<descriptors_1.rows; i++)
    {
        if (matches[i].distance <= max(2*min_dist, 0.02))
        {
            good_matches.push_back(matches[i]); 
        }
    }

    Mat img_matches; 
    drawMatches(img1, keypoints_1, img2, keypoints_2, 
                good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), 
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS); 
    
    imwrite("res.jpg", img_matches); 
    /*
    namedWindow("Good Matches", 0);
    resizeWindow("Good Matches", 800, 800); 
    imshow("Good Matches", img_matches); 
    */

    for (int i=0; i<(int)good_matches.size(); i++)
    {
        cout << "-- Good Match " << i 
             << " Keypoint 1: " << good_matches[i].queryIdx 
             << " Keypoint 2: " << good_matches[i].trainIdx 
             << endl; 
    }

    //waitKey(0); 
    return 0; 
}