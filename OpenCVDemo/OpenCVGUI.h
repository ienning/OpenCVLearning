﻿/*!*
    \file: OpenCVGUI.h
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
    int convertFourier();
    int yamlRead();    // yaml读取
    int yamlWrite();    // yaml写入

public:
    static void on_BoxFilter(int, void*);   // 边框过滤器
    static void on_MeanBlur(int, void*);    // 均值过滤器
    static void on_GaussianBlur(int, void*);    // 高斯过滤器
    static void on_MedianBlur(int, void*);  // 中值过滤器
    static void on_BilateraFilter(int, void*);  // 双边过滤器
    int filterEx(cv::Mat& img);
private:
    int m_boxFilterValue;
    int m_meanBlurValue;
    int m_gaussianBlurValue;
    int m_medianBlurValue;
    int m_bilateralFilterValue;
    cv::Mat m_filterSrcImage;
    cv::Mat m_filterResultImage1;
    cv::Mat m_filterResultImage2;
    cv::Mat m_filterResultImage3;
    cv::Mat m_filterResultImage4;
    cv::Mat m_filterResultImage5;

// 形态学练习
public:
    static void on_OpenClose(int, void*);   // 回调函数，开闭
    static void on_ErodeDilate(int, void*); // 腐蚀和膨胀
    static void on_TopBlackHat(int, void*); // 礼帽和黑帽
    static void ShowHelpTextx();            // 帮助文字显示
    int morphologyTs(cv::Mat& img);
private:
    int m_maxIterationNum = 10;
    int m_openCloseNum = 0;
    int m_erodeDilateNum = 0;
    int m_topBackHatNum = 0;
    int m_elementShape = MORPH_RECT;
    cv::Mat m_morphologySrcImage;
    cv::Mat m_morphologyResultImage1;
    cv::Mat m_morphologyResultImage2;
    cv::Mat m_morphologyResultImage3;


public:
    

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