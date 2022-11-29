#include "OpenCVGUI.h"
#include <string>

using namespace cv;
//OpenCVGUIDemo::rng = RNG(12345);

cv::RNG g_rng = cv::RNG(12345);
OpenCVGUIDemo::OpenCVGUIDemo()
{
    //std::cout << "Hello OpenCVGUI ���Ի�" << std::endl;
}

OpenCVGUIDemo::~OpenCVGUIDemo()
{

}

int OpenCVGUIDemo::erodeImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("腐蚀原图"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    erode(inputImg, outputImg, element);
    imshow("腐蚀结果图", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::blurImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("模糊原图"), inputImg);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    //erode(inputImg, outputImg, element);
    blur(inputImg, outputImg, ksize);
    imshow("模糊结果图", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::cannyImage(cv::Mat& inputImg, cv::Mat& outputImg, cv::Size ksize)
{
    imshow(std::string("模糊原图"), inputImg);
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
    imshow("模糊输出", outputImg);
    //waitKey(0);
    return 0;
}

int OpenCVGUIDemo::playVedio(cv::Mat& inputImg, cv::Mat& outputImg)
{
    //Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    //erode(inputImg, outputImg, element);
    //waitKey(0);
    //VideoCapture capture(0);
    VideoCapture capture("/home/ienning/Pictures/Data/cvTest/1/video.avi");
    while (1)
    {
        cv::Mat frame;
        capture >> frame;
        if (frame.empty())
            break;
        imshow("视频", frame);
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

void OpenCVGUIDemo::ShowHelpText()
{
    printf("Show Fourier image\n");
}

int OpenCVGUIDemo::convertFourier()
{
    // [1] using gray mode read image and showing
    Mat srcImage = imread("../cvTest/5/4_1.jpg", 0);
    if (srcImage.empty())
    {
        printf("Read image error, please sure this path if exist?\n");
        return false;
    }
    imshow("origin image", srcImage);
    ShowHelpText();

    // [2] extend input image to optimal size. border fill with 0
    int m = getOptimalDFTSize(srcImage.rows);
    int n = getOptimalDFTSize(srcImage.cols);
    Mat padded;
    copyMakeBorder(srcImage, padded, 0, m-srcImage.rows, 0, n-srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

    // [3] 为傅里叶变换的结果（实部和虚部）分配存储空间
    // 将planes数组组合合并成一个多通道的数组complexI
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);

    // [4]进行就地傅里叶变换
    dft(complexI, complexI);

    // [5]将复数转换为幅值，即=>log(1+sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);    // 将多通道数据组complexI分离成几个单通道数组,planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I));
    magnitude(planes[0], planes[1], planes[0]); // palens[0] = magnitude
    Mat magnitudeImage = planes[0];

    // [6]进行对数尺度(logarithmic scale) 缩放
    magnitudeImage += Scalar::all(1);
    log(magnitudeImage, magnitudeImage); //对自然对数

    // [7]剪切和重分布幅度图象限
    magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2,
                                    magnitudeImage.rows & -2));
    // 重新排列傅里叶图像中的象限，使得原点位于图像中心
    int cx = magnitudeImage.cols/2;
    int cy = magnitudeImage.rows/2;
    Mat q0(magnitudeImage, Rect(0, 0, cx, cy));     // ROI区域的左上
    Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));   // ROI区域的右上
    Mat q2(magnitudeImage, Rect(0, cy, cx, cy));    // ROI区域的左下
    Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));   // ROI区域的右下
    // 交换象限（左上和右下进行交换）
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    // 交换象限（左上和右下进行交换）
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    // [8]归一化，用0到1之间的浮点数将矩阵变换为可视化的图像格式
    normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

    imshow("频谱幅值", magnitudeImage);
    waitKey();

    return 0;
}



int OpenCVGUIDemo::yamlWrite()
{
    // 初始化
    FileStorage fs("../../cvTest/5/test.yaml", FileStorage::WRITE);
    // 开始文件写入
    fs << "frameCount" << 5;
    time_t rawTime;
    time(&rawTime);
    fs << "CalibrationDate" << asctime(localtime(&rawTime));
    Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
    Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
    fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
    fs <<"features" << "[";
    for (int i = 0; i < 3; i++)
    {
        int x = rand() % 640;
        int y = rand() % 480;
        uchar lbp = rand() % 256;
        fs <<"{:" << "x" << x << "y" << y << "lbp" << "[:";
        for (int j = 0; j < 8; j++)
        {
            fs << ((lbp >> j) & 1);
        }
        fs <<"]" << "}";
        
    }
    fs << "]";
    fs.release();
    printf("文件读写完毕，请在工程目录下查看生成的文件~");
    
    getchar();
    return 0;
}

int OpenCVGUIDemo::yamlRead()
{
    try
    {
        /* code */
        // change console font color

        // 初始化
        FileStorage fs("../../cvTest/5/test.yaml", FileStorage::READ);

        // 第一种方法，对FileNode操作
        int frameCount = (int)fs["frameCount"];

        std::string date;
        // 第二种方法，使用FileNode操作
        fs["calibrationDate"] >> date;

        Mat cameraMatrix2, distCoeffs2;
        fs["cameraMatrix"] >>cameraMatrix2;
        fs["distCoeffs"] >> distCoeffs2;
        
        std::cout << "frameCount: " << frameCount << std::endl
                  << "calibration date: " << date << std::endl
                  << "camera matrix: " << cameraMatrix2 << std::endl
                  << "distortion coeffs: " << distCoeffs2 << std::endl;
        FileNode features = fs["features"];
        FileNodeIterator it = features.begin(), it_end = features.end();
        int idx = 0;
        std::vector<uchar> lbpval;
        for (; it != it_end; it++, idx++)
        {
            std::cout << "feature #" << idx <<": ";
            std::cout << "x=" << (int)(*it)["x"] << ", y="
                      << (int)(*it)["y"] << ", lbp: (";
            (*it)["lbp"] >> lbpval;
            for (int i = 0; i < (int)lbpval.size(); i++)
            {
                std::cout << " " << (int)lbpval[i];
            }
            std::cout << ")" << std::endl;
        }
        fs.release();
        printf("\n 文件读取完毕，请输入任意键结束程序~");
        getchar();
        return 0;
        
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

}

int OpenCVGUIDemo::filterEx(cv::Mat& img)
{
    system("Color 5E");
    
    if (img.empty())
        return -1;
    m_boxFilterValue = 6;
    m_meanBlurValue=  10;
    m_gaussianBlurValue = 6;
    m_medianBlurValue = 10;
    m_bilateralFilterValue = 10;
    m_filterSrcImage = img.clone();
    m_filterResultImage1 = img.clone();
    m_filterResultImage2 = img.clone();
    m_filterResultImage3 = img.clone();
    m_filterResultImage4 = img.clone();
    m_filterResultImage5 = img.clone();
    namedWindow("[<0>原图窗口]", 1);
    imshow("[<0>原图窗口]", m_filterSrcImage);

    //==============================方框滤波======================================
    namedWindow("[<1>方框滤波]", 1);
    createTrackbar("内核值：", "[<1>方框滤波]", &m_boxFilterValue, 50, on_BoxFilter, this);
    on_BoxFilter(m_boxFilterValue, this);
    imshow("[<1>方框滤波]", m_filterResultImage1);

    //==============================均值滤波======================================
    namedWindow("[<2>均值滤波]", 1);
    createTrackbar("内核值：", "[<2>均值滤波]", &m_meanBlurValue, 50, on_MeanBlur, this);
    on_MeanBlur(m_meanBlurValue, this);
    imshow("[<2>均值滤波]", m_filterResultImage2);

    //==============================高斯滤波======================================
    namedWindow("[<3>高斯滤波]", 1);
    createTrackbar("内核值：", "[<3>高斯滤波]", &m_gaussianBlurValue, 50, on_GaussianBlur, this);
    on_GaussianBlur(m_gaussianBlurValue, this);
    imshow("[<3>高斯滤波]", m_filterResultImage3);

    //==============================中值滤波======================================
    namedWindow("[<4>中值滤波]", 1);
    createTrackbar("内核值：", "[<4>中值滤波]", &m_medianBlurValue, 50, on_MedianBlur, this);
    on_MedianBlur(m_medianBlurValue, this);
    imshow("[<4>中值滤波]", m_filterResultImage4);

    //==============================双边滤波======================================
    namedWindow("[<5>双边滤波]", 1);
    createTrackbar("内核值：", "[<5>双边滤波]", &m_bilateralFilterValue, 50, on_BilateraFilter, this);
    on_BilateraFilter(m_bilateralFilterValue, this);
    imshow("[<5>双边滤波]", m_filterResultImage5);

    while (char(waitKey(1)) != 'q')
    {
        /* code */
    }
    return 0;
    
}

void OpenCVGUIDemo::on_BoxFilter(int, void* ptr)
{
    OpenCVGUIDemo* cvDemoPtr = (OpenCVGUIDemo*) ptr;
    boxFilter(cvDemoPtr->m_filterSrcImage, cvDemoPtr->m_filterResultImage1, -1,
              Size(cvDemoPtr->m_boxFilterValue+1, cvDemoPtr->m_boxFilterValue));
    imshow("[<1>方框滤波]", cvDemoPtr->m_filterResultImage1);
}

void OpenCVGUIDemo::on_MeanBlur(int, void* ptr)
{
    OpenCVGUIDemo* cvDemoPtr = (OpenCVGUIDemo*) ptr;
    blur(cvDemoPtr->m_filterSrcImage, cvDemoPtr->m_filterResultImage2,
         Size(cvDemoPtr->m_meanBlurValue+1, cvDemoPtr->m_meanBlurValue+1));
    imshow("[<2>均值滤波]", cvDemoPtr->m_filterResultImage2);
}

void OpenCVGUIDemo::on_GaussianBlur(int, void* ptr)
{
    OpenCVGUIDemo* cvDemoPtr = (OpenCVGUIDemo*) ptr;
    GaussianBlur(cvDemoPtr->m_filterSrcImage, cvDemoPtr->m_filterResultImage3,
                 Size(cvDemoPtr->m_gaussianBlurValue*2+1, cvDemoPtr->m_gaussianBlurValue*2+1),
                 0, 0);
    imshow("[<3>高斯滤波]", cvDemoPtr->m_filterResultImage3);
}

void OpenCVGUIDemo::on_MedianBlur(int, void* ptr)
{
    OpenCVGUIDemo* cvDemoPtr = (OpenCVGUIDemo*) ptr;
    medianBlur(cvDemoPtr->m_filterSrcImage, cvDemoPtr->m_filterResultImage4,
                cvDemoPtr->m_medianBlurValue*2+1);
    imshow("[<4>中值滤波]", cvDemoPtr->m_filterResultImage4);
}

void OpenCVGUIDemo::on_BilateraFilter(int, void* ptr)
{
    OpenCVGUIDemo* cvDemoPtr = (OpenCVGUIDemo*) ptr;
    bilateralFilter(cvDemoPtr->m_filterSrcImage, cvDemoPtr->m_filterResultImage5,
                    cvDemoPtr->m_bilateralFilterValue, cvDemoPtr->m_bilateralFilterValue*2,
                    cvDemoPtr->m_bilateralFilterValue/2);
    imshow("[<5>双边滤波]", cvDemoPtr->m_filterResultImage5);
}

int OpenCVGUIDemo::morphologyTs(cv::Mat& image)
{
    if (image.empty())
    {
        return;
    }
    namedWindow("[原始图]");
    imshow("[原始图]");
    namedWindow("[开运算/闭运算]", 1);
    namedWindow("[腐蚀/膨胀]", 1);
    namedWindow("[顶帽/黑帽]", 1);
    createTrackbar("迭代值", "[开运算/闭运算]", &m_openCloseNum,
                   on_OpenClose, this);
    createTrackbar("迭代值", "[腐蚀/膨胀]", &m_erodeDilateNum,
                   on_ErodeDilate, this);
    createTrackbar("迭代值", "[顶帽/礼帽]", &m_topBackHatNum,
                   on_TopBlackHat, this);
    while (1)
    {
        int c;
        on_OpenClose(m_openCloseNum, this);
        on_ErrodeDilate(m_erodeDilateNum, this);
        on_TopBlackHat(m_topBackHatNum, this);

        c = waitKey(0);
        
        if ((char) c== 'q' || (char)c == 27)
            break;
        if ((char)c == 49)
        {
            m_elementShape = MORPH_ELLIPSE;
        }
        else if ((char)c == 50)
        {
            m_elementShape = MORPH_RECT;
        }
        else if ((char)c == 51)
        {
            m_elementShape = MORPH_CROSS;
        }
        else if ((char)c == ' ')
        {
            m_elementShape = (m_elementShape+1)%3;
        }
        
    }
    return 0;
    
    
}

void OpenCVGUIDemo::on_OpenClose(int, void* ptr)
{
    OpenCVGUIDemo* cvDemoPtr = (OpenCVGUIDemo*) ptr;
    int offset = cvDemoPtr->m_openCloseNum - cvDemoPtr->m_maxIterationNum;
    int absolute_offset = offset >= 0 ? offset : -offset;
    Mat element = getStructuringElement(cvDemoPtr->m_elementShape, 
                                        Size(absolute_offset*2+1, absolute_offset*2+1),
                                        Point(absolute_offset, absolute_offset));
    if (offset < 0)
    {
        morphologyEx(cvDemoPtr->m_morphologySrcImage, cvDemoPtr->m_morphologyResultImage1,
                     MORPH_OPEN, element);
    }
    else
    {
        morphologyEx(cvDemoPtr->m_morphologySrcImage, cvDemoPtr->m_morphologyResultImage1, 
                     MORPH_CLOSE, element);
    }
    imshow("[开运算/闭运算]", cvDemoPtr->m_morphologyResultImage1);
}

void OpenCVGUIDemo::on_ErodeDilate()
{
    OpenCVGUIDemo* cvDemoPtr = (OpenCVGUIDemo*) ptr;
    int offset = cvDemoPtr->m_erodeDilateNum - cvDemoPtr->m_maxIterationNum;
    int absoluteOffset = offset < 0 ? -offset : offset;
    Mat element = getStructuringElement(cvDemoPtr->m_elementShape, Size(absoluteOffset*2+1, absoluteOffset*2+1),
                                        Point(absoluteOffset, absoluteOffset));
    if (offset < 0)
    {
        erode(cvDemoPtr->m_morphologySrcImage, cvDemoPtr->m_morphologyResultImage2,
                     element);
    }
    else
    {
        dilate(cvDemoPtr->m_morphologySrcImage, cvDemoPtr->m_morphologyResultImage2,
                     element);
    }
    imshow("[腐蚀/膨胀]");
    
}

// 礼帽和黑帽运算
void OpenCVGUIDemo::on_TopBlackHat()
{
    OpenCVGUIDemo* cvDemoPtr = (OpenCVGUIDemo*) ptr;
    int offset = cvDemoPtr->m_topBackHatNum - cvDemoPtr->m_maxIterationNum;
    int absoluteOffset = offset < 0 ? -offset : offset;
    Mat element = getStructuringElement(cvDemoPtr->m_elementShape, Size(absoluteOffset*2+1, absoluteOffset*2+1),
                                        Point(absoluteOffset, absoluteOffset));
    if (offset < 0)
    {
        /* code */
        morphologyEx(cvDemoPtr->m_morphologySrcImage, cvDemoPtr->m_morphologyResultImage3,
                      MORPH_TOPHAT, element);
    }
    else
    {
        morphologyEx(cvDemoPtr->m_morphologySrcImage, cvDemoPtr->m_morphologyResultImage3,
                     MORPH_BLACKHAT, element);
    }
    imshow("[顶帽/黑帽]");
    
}

void OpenCVGUIDemo::ShowHelpTextx()
{

}