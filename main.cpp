#include <iostream>
#include <string>
#include "OpenCVDemo/OpenCVGUI.h"

int main(int argc, const char** argv) {
    //std::cout << "hello world!" << std::endl;
    OpenCVGUIDemo openCVGUIDemo;
    cv::Mat img = cv::imread("D:/Data/cvTest/1/erode.jpg");
    cv::Mat outImg;
    openCVGUIDemo.erodeImage(img, outImg);

    return 0;
}