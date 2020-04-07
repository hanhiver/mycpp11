#include <iostream> 
#include <vector> 
#include <chrono>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/cudafeatures2d.hpp>

using namespace std;

#if 0
int GetMatchPointCount(const char * pic_path_1,const char * pic_path_2) 
{
  /*指定使用的GPU序号，相关的还有下面几个函数可以使用
    cv::cuda::getCudaEnabledDeviceCount();
    cv::cuda::getDevice();
    cv::cuda::DeviceInfo*/
  cv::cuda::setDevice(0);

  /*向显存加载两张图片。这里需要注意两个问题：
    第一，我们不能像操作（主）内存一样直接一个字节一个字节的操作显存，也不能直接从外存把图片加载到显存，一般需要通过内存作为媒介
    第二，目前opencv的GPU SURF仅支持8位单通道图像，所以加上参数IMREAD_GRAYSCALE*/
  cv::cuda::GpuMat gmat1;
  cv::cuda::GpuMat gmat2;
  gmat1.upload(cv::imread(pic_path_1,cv::IMREAD_GRAYSCALE));
  gmat2.upload(cv::imread(pic_path_2,cv::IMREAD_GRAYSCALE));

  /*下面这个函数的原型是：
  explicit SURF_CUDA(double 
      _hessianThreshold, //SURF海森特征点阈值
      int _nOctaves=4, //尺度金字塔个数
      int _nOctaveLayers=2, //每一个尺度金字塔层数
      bool _extended=false, //如果true那么得到的描述子是128维，否则是64维
      float _keypointsRatio=0.01f, 
      bool _upright = false 
      );
  要理解这几个参数涉及SURF的原理*/
  cv::cuda::SURF_CUDA surf(
      100,4,3
      );  

  /*分配下面几个GpuMat存储keypoint和相应的descriptor*/
  cv::cuda::GpuMat keypt1,keypt2;
  cv::cuda::GpuMat desc1,desc2;

  /*检测特征点*/
  surf(gmat1,cv::cuda::GpuMat(),keypt1,desc1);
  surf(gmat2,cv::cuda::GpuMat(),keypt2,desc2);

  /*匹配，下面的匹配部分和CPU的match没有太多区别,这里新建一个Brute-Force Matcher，一对descriptor的L2距离小于0.1则认为匹配*/
  auto matcher=cv::cuda::DescriptorMatcher::createBFMatcher(cv::NORM_L2);
  vector<cv::DMatch> match_vec;
  matcher->match(desc1,desc2,match_vec);

  int count=0;
  for(auto & d:match_vec){
    if(d.distance<0.1) count++;
  }
  return count;
}

int main(int argc, const char* argv[])
{
  GetMatchPointCount("surf_pic1.jpg","surf_pic2.jpg");
  return 0;
}  
#endif

int main()
{
    cv::Mat img1 = cv::imread("surf_pic1.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread("surf_pic2.jpg", cv::IMREAD_GRAYSCALE); 

    if ((img1.data == NULL) || (img2.data == NULL))
    {
        cout << "Read images failed. " << endl; 
        return -1; 
    }

    // Use the first GPU devices. 
    cv::cuda::setDevice(0);

    // Create two GPU mat and upload the images. 
    auto start = std::chrono::high_resolution_clock::now();
    cv::cuda::GpuMat gmat1; 
    cv::cuda::GpuMat gmat2;
    gmat1.upload(img1);
    gmat2.upload(img2);
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double period = double(dur.count());
    std::cout << "Create GpuMat and upload images: " << period << " us." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    cv::cuda::SURF_CUDA surf_gpu(1000);

    // Create GpuMat to store the keypoints and relevant descritors. 
    cv::cuda::GpuMat keypt1, keypt2;
    cv::cuda::GpuMat desc1, desc2;

    // Caculate the SURF. 
    surf_gpu(gmat1, cv::cuda::GpuMat(), keypt1, desc1);
    surf_gpu(gmat2, cv::cuda::GpuMat(), keypt2, desc2);

    end = std::chrono::high_resolution_clock::now();
    dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    period = double(dur.count());
    std::cout << "Create and caculate surf: " << period << " us." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    vector<cv::KeyPoint> keypt1_host;
    vector<cv::KeyPoint> keypt2_host;
    surf_gpu.downloadKeypoints(keypt1, keypt1_host);
    surf_gpu.downloadKeypoints(keypt2, keypt2_host);
    end = std::chrono::high_resolution_clock::now();
    dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    period = double(dur.count());
    std::cout << "Download keypoints from GPU: " << period << " us." << std::endl;


    start = std::chrono::high_resolution_clock::now();
    // Create Brute-Force Matcher. 
    auto matcher = cv::cuda::DescriptorMatcher::createBFMatcher(cv::NORM_L2);
    vector<cv::DMatch> match_vect; 
    matcher->match(desc1, desc2, match_vect);
    end = std::chrono::high_resolution_clock::now();
    dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    period = double(dur.count());
    std::cout << "Create and caculate matchs: " << period << " us." << std::endl;

    double max_dist = 0; 
    double min_dist = 100; 

    for (int i=0; i<desc1.rows; i++)
    {
        double dist = match_vect[i].distance;
        if (dist < min_dist) min_dist = dist; 
        if (dist > max_dist) max_dist = dist; 
    }

    cout << "-- Max dist: " << max_dist << endl; 
    cout << "-- Min dist: " << min_dist << endl; 

    vector<cv::DMatch> good_matches;
    for (int i=0; i<desc1.rows; i++)
    {
        if (match_vect[i].distance <= max(2*min_dist, 0.02))
        {
            good_matches.push_back(match_vect[i]);
        }
    }

    for (int i=0; i<(int)good_matches.size(); i++)
    {
        cout << "-- Good Match " << i 
             << " Keypoint 1: " << good_matches[i].queryIdx 
             << " Keypoint 2: " << good_matches[i].trainIdx 
             << endl; 
    }

    return 0; 
}
