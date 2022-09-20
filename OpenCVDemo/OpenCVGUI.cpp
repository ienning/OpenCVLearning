#include "OpenCVGUI.h"
#include <string>

using namespace cv;
//OpenCVGUIDemo::rng = RNG(12345);

cv::RNG g_rng = cv::RNG(12345);
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

int OpenCVGUIDemo::mouseTracking()
{
    m_rectangle = Rect(-1, -1, 0, 0);
    Mat tempImage;
    m_srcImage = Mat(600, 800, CV_8UC3);
    m_srcImage.copyTo(tempImage);
    //m_rectangle = Rect(-1, -1, 0, 0);
    m_srcImage = Scalar::all(0);
    
    // 2. 设置鼠标操作回调函数
    namedWindow(WINDOW_NAME);
    //setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);
    setMouseCallback(WINDOW_NAME, on_MouseHandle, this);

    // 3. 程序主循环，当进行回执的标识符为真时，进行绘制
    while (1)
    {
        m_srcImage.copyTo(tempImage);
        if (m_bDrawingBox)
            drawRectangle(tempImage, m_rectangle);
        imshow (WINDOW_NAME, tempImage);
        if (waitKey(10) == 27)
            break;
    }
    return 0;

}

void OpenCVGUIDemo::on_MouseHandle(int event, int x, int y, int flags, void* param)
{
    OpenCVGUIDemo* cvDemo = (OpenCVGUIDemo*)param;
    Mat& image = cvDemo->m_srcImage;
    switch (event)
    {
    case EVENT_MOUSEMOVE:
    {
        if (cvDemo->m_bDrawingBox)
        {
            cvDemo->m_rectangle.width = x-cvDemo->m_rectangle.x;
            cvDemo->m_rectangle.height = y-cvDemo->m_rectangle.y;
        }
        break;
    }
    case EVENT_LBUTTONDOWN:
    {
        cvDemo->m_bDrawingBox = true;
        cvDemo->m_rectangle = Rect(x, y, 0, 0); // 记录起始点
        break;
    }
    case EVENT_LBUTTONUP:
    {
        cvDemo->m_bDrawingBox = false;
        if (cvDemo->m_rectangle.width < 0)
        {
            cvDemo->m_rectangle.x += cvDemo->m_rectangle.width;
            cvDemo->m_rectangle.width *= -1;
        }
        if (cvDemo->m_rectangle.height < 0)
        {
            cvDemo->m_rectangle.y += cvDemo->m_rectangle.height;
            cvDemo->m_rectangle.height *= -1;
        }
        drawRectangle(image, cvDemo->m_rectangle);
    }
    
    default:
        break;
    }
}

int OpenCVGUIDemo::drawRectangle(Mat& image, Rect& rect)
{
    rectangle(image, rect.tl(), rect.br(), Scalar(g_rng.uniform(0, 255), 
    g_rng.uniform(0, 255), g_rng.uniform(0, 255))); // 随机颜色
    return 0;
}

#define WINDOW_WIDTH 1000
void OpenCVGUIDemo::DrawEllipse(cv::Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;
    ellipse(img,
            Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2),
            Size(WINDOW_WIDTH/4, WINDOW_WIDTH/16),
            angle,
            0,
            360,
            Scalar(255, 129, 0),
            thickness,
            lineType
    );
    imshow(WINDOW_NAME, img);
}

bool OpenCVGUIDemo::ROI_AddImage()
{
    Mat srcImage1 = imread("../cvTest/5/dota_pa.jpg");
    Mat logoImage = imread("../cvTest/5/dota_logo.jpg");
    if (!srcImage1.data)
    {
        printf("读取srcImage1 错误！\n");
        return false;
    }
    if (!logoImage.data)
    {
        printf("读取logoImage 错误！\n");
        return false;
    }
    Mat imageROI1 = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));
    // [3]加载掩模（必须使用灰度图）
    Mat mask = imread("../cvTest/5/dota_logo.jpg", 0);
    logoImage.copyTo(imageROI1, mask);
    namedWindow("使用ROI实现图像叠加实例窗口");
    imshow("利用ROI实现图像叠加实例窗口", srcImage1);
    return true;
}

int OpenCVGUIDemo::contrastAndBright()
{
    m_srcImage = imread("../cvTest/5/3_1.jpg");
    if (!m_srcImage.data)
    {
        printf("读取图片错误，请确定目录下是否有imread函数指定图片存在！");
        return -1;
    }
    m_destImage = Mat::zeros(m_srcImage.size(), m_srcImage.type());
    m_nContrastValue = 80;
    m_nBrightValue = 80;
    namedWindow("【效果图窗口】", 1);
    createTrackbar("对比度：", "【效果图窗口】", &m_nContrastValue, 300, on_ContrastAndBright, this);
    createTrackbar("亮  度：", "【效果图窗口】", &m_nBrightValue, 200, on_ContrastAndBright, this);
    on_ContrastAndBright(m_nContrastValue, this);
    on_ContrastAndBright(m_nBrightValue, this);
    while (char(waitKey(1)) != 'q')
    {
        
    }
    return 0;
    
}

void OpenCVGUIDemo::on_ContrastAndBright(int value, void* point)
{
    OpenCVGUIDemo* demo = (OpenCVGUIDemo*) point;
    namedWindow("【原始图像窗口】", 1);
    for (int y = 0; y < demo->m_srcImage.rows; y++)
    {
        for (int x = 0; x < demo->m_srcImage.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                demo->m_destImage.at<Vec3b>(y, x)[c] =
                saturate_cast<uchar>((demo->m_nContrastValue*0.01)*(demo->m_srcImage.at<Vec3b>(y, x)[c])+
                demo->m_nBrightValue);
            }
            
        }
        imshow("【原始图像窗口】", demo->m_srcImage);
        imshow("【效果图窗口】", demo->m_destImage);
    }
}

