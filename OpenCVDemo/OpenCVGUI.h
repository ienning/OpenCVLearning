/*!*
    \file: 
    \author: ienning
*/
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
    int erodeImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size size=cv::Size(7,7));
    int blurImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size size=cv::Size(7,7));
    int cannyImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size size=cv::Size(7,7));
    int playVedio(cv::Mat& inputImg, cv::Mat& outputImg);
    int primaryMixImage();
    static void on_trackbar(int, void*);
    int sliderBar(); // 滑动条
public:
    const int m_nMaxAlphaValue = 100;
    int m_nAlphaValueSilder;
    double m_dBetaValue;
    double m_dAlphaValue;
    cv::Mat m_srcImage1;
    cv::Mat m_srcImage2;
    cv::Mat m_srcImage;

private:
    cv::Mat m_originMat;
};

#endif //OPENCVDEMO_OPENCVGUI_H__