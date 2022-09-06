#include "OpenCVGUI.h"
#include <string>

using namespace cv;

OpenCVGUIDemo::OpenCVGUIDemo()
{
    std::cout << "Hello OpenCVGUI 测试机" << std::endl;
}

OpenCVGUIDemo::~OpenCVGUIDemo()
{

}

int OpenCVGUIDemo::erodeImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("原图腐蚀操作"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode(inputImg, outputImg, element);
    imshow("效果图腐蚀操作", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::blurImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("原图模糊操作"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    //erode(inputImg, outputImg, element);
    blur(inputImg, outputImg, ksize);
    imshow("效果图模糊操作", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::cannyImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("原图边缘检测操作"), inputImg);
    cv::Mat transImg;
    if (inputImg.channels() == 3)
    {
        cv::cvtColor(inputImg, transImg, cv::COLOR_BGR2GRAY);
    }
    else if (inputImg.channels() == 1){
        transImg = inputImg;
    }
    else
    {
        return -1;
    }
    cv::Mat blurImg;
    blurImage(transImg, blurImg);
    Canny(blurImg, outputImg, 3, 9);
    //Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    //erode(inputImg, outputImg, element);
    imshow("效果图边缘检测操作", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::playVedio(cv::Mat& inputImg, cv::Mat& outputImg)
{
    //imshow(std::string("原图腐蚀操作"), inputImg);
    //Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    //erode(inputImg, outputImg, element);
    //imshow("效果图腐蚀操作", outputImg);
    //waitKey(0);
    //VideoCapture capture(0);
    VideoCapture capture("/home/ienning/Pictures/Data/cvTest/1/video.avi");
    while (1)
    {
        cv::Mat frame;
        capture >> frame;
        if (frame.empty())
            break;
        imshow("读取视频", frame);
        waitKey(30); // delay 30ms
    }
    return 0;
}
