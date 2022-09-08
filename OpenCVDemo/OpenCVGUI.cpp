#include "OpenCVGUI.h"
#include <string>

using namespace cv;

OpenCVGUIDemo::OpenCVGUIDemo()
{
    std::cout << "Hello OpenCVGUI ���Ի�" << std::endl;
}

OpenCVGUIDemo::~OpenCVGUIDemo()
{

}

int OpenCVGUIDemo::erodeImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("ԭͼ��ʴ����"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode(inputImg, outputImg, element);
    imshow("Ч��ͼ��ʴ����", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::blurImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("ԭͼģ������"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    //erode(inputImg, outputImg, element);
    blur(inputImg, outputImg, ksize);
    imshow("Ч��ͼģ������", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::cannyImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("ԭͼ��Ե������"), inputImg);
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
    imshow("Ч��ͼ��Ե������", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::playVedio(cv::Mat& inputImg, cv::Mat& outputImg)
{
    //imshow(std::string("ԭͼ��ʴ����"), inputImg);
    //Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    //erode(inputImg, outputImg, element);
    //imshow("Ч��ͼ��ʴ����", outputImg);
    //waitKey(0);
    //VideoCapture capture(0);
    VideoCapture capture("/home/ienning/Pictures/Data/cvTest/1/video.avi");
    while (1)
    {
        cv::Mat frame;
        capture >> frame;
        if (frame.empty())
            break;
        imshow("��ȡ��Ƶ", frame);
        waitKey(30); // delay 30ms
    }
    return 0;
}

int OpenCVGUIDemo::primaryMixImage()
{
    try
    {
        Mat girl = imread("../cvTest/3/girl.jpg");    
        namedWindow("[1]动漫图");   // 创建窗口
        imshow("[1]动漫图", girl);  // 显示窗口
        
        // mix image
        Mat image = imread("../cvTest/3/dota.jpg", -1);
        Mat logo = imread("../cvTest/3/dota_logo.jpg");
        namedWindow("[2]原画图");
        imshow("[2]原画图", image);

        namedWindow("[3]原画图");
        imshow("[3]原画图", image);

        namedWindow("[3]logo图");
        imshow("[3]logo图", logo);

        Mat imageROI;
        imageROI = image(Rect(800, 350, logo.cols, logo.rows));
        addWeighted(imageROI, 0.5, logo, 0.3, 0, imageROI);

        namedWindow("[4]原图+logo图");
        imshow("[4]原图+logo图", image);

        imwrite("由imwrite生产的图片.jpg", image);
    }
    catch (std::exception& e)
    {
        return -1;
    }
    return 0;
}

#define WINDOW_NAME "【线性混合实例】"
void OpenCVGUIDemo::on_trackbar(int, void* point)
{
    
    OpenCVGUIDemo* cvDemo = (OpenCVGUIDemo*)point;
    cvDemo->m_dAlphaValue = (double) cvDemo->m_nAlphaValueSilder/cvDemo->m_nMaxAlphaValue;
    cvDemo->m_dBetaValue = (1.0 - cvDemo->m_dAlphaValue);
    addWeighted(cvDemo->m_srcImage1, cvDemo->m_dAlphaValue, cvDemo->m_srcImage2, cvDemo->m_dBetaValue,
    0, cvDemo->m_srcImage);
    imshow(WINDOW_NAME, cvDemo->m_srcImage);
}

int OpenCVGUIDemo::sliderBar()
{
    m_srcImage1 = imread("../cvTest/3/1.jpg");
    m_srcImage2 = imread("../cvTest/3/2.jpg");
    if (m_srcImage1.empty())
    {
        printf("读取第一张图片错误，请确认目录下是否有imread函数指定的图片\n");
        return -1;
    }
    if (m_srcImage2.empty())
    {
        printf("读取第一张图片错误，请确认目录下是否有imread函数指定的图片\n");
        return -1;
    }
    m_nAlphaValueSilder = 70;
    namedWindow(WINDOW_NAME, 1);
    char trackbarName[50];
    sprintf(trackbarName, "透明值 %d", m_nMaxAlphaValue);
    createTrackbar(trackbarName, WINDOW_NAME, &m_nAlphaValueSilder, m_nMaxAlphaValue, on_trackbar, this);
    on_trackbar(m_nAlphaValueSilder, this);
    return 0;
}