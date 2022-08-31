#ifndef OPENCVDEMO_OPENCVGUI_H__
#define OPENCVDEMO_OPENCVGUI_H__
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

class OpenCVGUIDemo
{
public:
    OpenCVGUIDemo();
    ~OpenCVGUIDemo();
    int erodeImage(cv::Mat& inputImg, cv::Mat& outputImg);
    int blurImage(cv::Mat& inputImg, cv::Mat& outputImg);
    int cannyImage(cv::Mat& inputImg, cv::Mat& outputImg);
    int playVedio(cv::Mat& inputImg, cv::Mat& outputImg);

private:
    cv::Mat m_originMat;
};

#endif //OPENCVDEMO_OPENCVGUI_H__