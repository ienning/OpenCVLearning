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

int OpenCVGUIDemo::erodeImage(cv::Mat& inputImg, cv::Mat& outputImg)
{
    imshow(std::string("原图腐蚀操作"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode(inputImg, outputImg, element);
    imshow("效果图腐蚀操作", outputImg);
    waitKey(0);
    return 0;
}

int OpenCVGUIDemo::blurImage(cv::Mat& inputImg, cv::Mat& outputImg)
{
    imshow(std::string("原图模糊操作"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode(inputImg, outputImg, element);
    imshow("效果图模糊操作", outputImg);
    waitKey(0);
    return 0;
}

int OpenCVGUIDemo::cannyImage(cv::Mat& inputImg, cv::Mat& outputImg)
{
    imshow(std::string("原图腐蚀操作"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode(inputImg, outputImg, element);
    imshow("效果图腐蚀操作", outputImg);
    waitKey(0);
    return 0;
}

int OpenCVGUIDemo::playVedio(cv::Mat& inputImg, cv::Mat& outputImg)
{
    imshow(std::string("原图腐蚀操作"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode(inputImg, outputImg, element);
    imshow("效果图腐蚀操作", outputImg);
    waitKey(0);
    return 0;
}
