#include <iostream>
#include <string>
#include "OpenCVDemo/OpenCVGUI.h"
#include <unistd.h>

int main(int argc, const char** argv) {
    //std::cout << "hello world!" << std::endl;
    OpenCVGUIDemo openCVGUIDemo;
    //cv::Mat img = cv::imread("D:/Data/cvTest/1/erode.jpg");
    //cv::Mat img = cv::imread("D:/Data/cvTest/1/blur.jpg");
    //cv::Mat img = cv::imread("D:/Data/cvTest/1/canny.jpg");
    //cv::Mat img = cv::imread("/home/ienning/Pictures/Data/cvTest/1/canny.jpg");
    cv::Mat img = cv::imread("../cvTest/1/canny.jpg");
    cv::Mat outImg;
    std::cout << "test" << std::endl;
    //openCVGUIDemo.erodeImage(img, outImg);
    //openCVGUIDemo.blurImage(img, outImg);
    openCVGUIDemo.cannyImage(img, outImg);
    //char path[255];
    //getcwd(path, 255);
    //std::cout << "path: " << path << std::endl;
    cv::waitKey(0);
    //openCVGUIDemo.playVedio(img, outImg);
    return 0;
}