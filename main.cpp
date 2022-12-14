#include <iostream>
#include <string>
#include "OpenCVDemo/OpenCVGUI.h"

int main(int argc, const char** argv) {
    //std::cout << "hello world!" << std::endl;
    OpenCVGUIDemo openCVGUIDemo;
    //cv::Mat img = cv::imread("D:/Data/cvTest/1/erode.jpg");
    //cv::Mat img = cv::imread("D:/Data/cvTest/1/blur.jpg");
    //cv::Mat img = cv::imread("D:/Data/cvTest/1/canny.jpg");
    //cv::Mat img = cv::imread("/home/ienning/Pictures/Data/cvTest/1/canny.jpg");
    //cv::Mat img = cv::imread("../cvTest/1/canny.jpg");
    //cv::Mat img = cv::imread("../cvTest/5/4_1.jpg");
    //double angle = 5;
    //cv::Mat outImg;
    //std::cout << "test" << std::endl;
    //openCVGUIDemo.erodeImage(img, outImg);
    //openCVGUIDemo.blurImage(img, outImg);
    //openCVGUIDemo.cannyImage(img, outImg);
    //char path[255];
    //getcwd(path, 255);
    //std::cout << "path: " << path << std::endl;
    //openCVGUIDemo.primaryMixImage();
    //openCVGUIDemo.sliderBar();
    //openCVGUIDemo.mouseTracking();
    //openCVGUIDemo.DrawEllipse(img, angle);
    //openCVGUIDemo.ROI_AddImage();
    //openCVGUIDemo.contrastAndBright();
    //openCVGUIDemo.convertFourier();
    //openCVGUIDemo.yamlWrite();
    //openCVGUIDemo.yamlRead();

    // Filter
    //cv::Mat img = cv::imread("../../cvTest/6/2.jpg");
    //openCVGUIDemo.filterEx(img);

    // morphonoly
    //cv::Mat img = cv::imread("../../cvTest/6/5.jpg");
    //openCVGUIDemo.morphologyTs(img);

    // pyramid and resize
    //cv::Mat img = cv::imread("../../cvTest/6/8.jpg");
    //openCVGUIDemo.pyramidAndResize(img);

    // threshold ops
    //cv::Mat img = cv::imread("../../cvTest/6/10.jpg");
    //openCVGUIDemo.thresholdOps(img);

    // EdgeDetection
    //cv::Mat img = cv::imread("../../cvTest/7/1.jpg");
    //openCVGUIDemo.edgeDetect(img);

    // HoughTransform
    cv::Mat img = cv::imread("../../cvTest/7/2.jpg");
    openCVGUIDemo.HoughConvert(img);

    cv::waitKey(0);
    //openCVGUIDemo.playVedio(img, outImg);
    return 0;
}