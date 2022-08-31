#include <iostream>
#include <string>
#include "OpenCVDemo/OpenCVGUI.h"

int main(int argc, const char** argv) {
    //std::cout << "hello world!" << std::endl;
    OpenCVGUIDemo openCVGUIDemo;
    //cv::Mat img = cv::imread("D:/Data/cvTest/1/erode.jpg");
    //cv::Mat img = cv::imread("D:/Data/cvTest/1/blur.jpg");
    cv::Mat img = cv::imread("D:/Data/cvTest/1/canny.jpg");
    cv::Mat outImg;
    //openCVGUIDemo.erodeImage(img, outImg);
    //openCVGUIDemo.blurImage(img, outImg);
    openCVGUIDemo.cannyImage(img, outImg);
    cv::waitKey(0);
    return 0;
}