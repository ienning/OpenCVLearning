#include "OpenCVGUI.h"
#include <string>

using namespace cv;

OpenCVGUIDemo::OpenCVGUIDemo()
{
    std::cout << "Hello OpenCVGUI ²âÊÔ»ú" << std::endl;
}

OpenCVGUIDemo::~OpenCVGUIDemo()
{

}

int OpenCVGUIDemo::erodeImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("Ô­Í¼¸¯Ê´²Ù×÷"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode(inputImg, outputImg, element);
    imshow("Ð§¹ûÍ¼¸¯Ê´²Ù×÷", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::blurImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("Ô­Í¼Ä£ºý²Ù×÷"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    //erode(inputImg, outputImg, element);
    blur(inputImg, outputImg, ksize);
    imshow("Ð§¹ûÍ¼Ä£ºý²Ù×÷", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::cannyImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("Ô­Í¼±ßÔµ¼ì²â²Ù×÷"), inputImg);
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
    imshow("Ð§¹ûÍ¼±ßÔµ¼ì²â²Ù×÷", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::playVedio(cv::Mat& inputImg, cv::Mat& outputImg)
{
    imshow(std::string("Ô­Í¼¸¯Ê´²Ù×÷"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode(inputImg, outputImg, element);
    imshow("Ð§¹ûÍ¼¸¯Ê´²Ù×÷", outputImg);
    //waitKey(0);
    return 0;
}
