/*!*
    \file: 
    \author: ienning
*/
#ifndef OPENCVDEMO_OPENCVGUI_H__
#define OPENCVDEMO_OPENCVGUI_H__
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

extern cv::RNG g_rng;
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
    static void on_MouseHandle(int event, int x, int y, int flags, void* param);
    int mouseTracking();    // 鼠标跟踪操作
    static int drawRectangle(cv::Mat& image, cv::Rect& rect);
    void DrawEllipse(cv::Mat img, double angle);
    bool ROI_AddImage();
    static void on_ContrastAndBright(int, void*);
    static void ShowHelpText();
    int contrastAndBright();
public:
    const int m_nMaxAlphaValue = 100;
    int m_nAlphaValueSilder;
    double m_dBetaValue;
    double m_dAlphaValue;
    cv::Mat m_srcImage1;
    cv::Mat m_srcImage2;
    cv::Mat m_srcImage;

    cv::Rect m_rectangle;
    bool m_bDrawingBox = false;
    
    // brightness and contrast
    int m_nContrastValue;
    int m_nBrightValue;
    //uchar m_nBrightValue;
    cv::Mat m_destImage;

private:
    cv::Mat m_originMat;
};

#endif //OPENCVDEMO_OPENCVGUI_H__