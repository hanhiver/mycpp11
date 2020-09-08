//使用这个类时，需要配置freetype库。对于含有  
//CMakeLists.txt的项目，请参考本项目中的配置。
#include <string> 

#include "opencv2/opencv.hpp"
#include "CvText.h"

using namespace Utils;
/*
void func{
    //其他代码
    Mat mat = ...;
    CvText text("simhei.ttf");//载入字体文件
    std::string str = "EnglishTest中文测试";//替换成需要输出的字符串
    Point pos(5,25);//输出起始位置
    Scalar color(255,255,255);//字的颜色，默认为白色
    text.putText(mat,str,pos,color);//输出文字
    //其他代码
}

#include "opencv2/opencv.hpp"
 
#include "putText.h"
*/
using namespace std;
using namespace cv;
 
int main()
{
    // Mat img = imread("src.jpg");
    Mat img = cv::imread(cv::samples::findFile("lena.jpg"));
    CvText text("/home/hd275562/INSTALL/simhei.ttf");
    std::string str = "EnglishTest中文测试";

    std::cout << "Done. " << std::endl; 
    //imshow("test", img);
    //waitKey();
 
    return 0;   
}

