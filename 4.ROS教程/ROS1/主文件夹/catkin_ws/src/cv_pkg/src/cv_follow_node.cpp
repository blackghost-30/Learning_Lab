#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>            // 转换格式头文件
#include <sensor_msgs/image_encodings.h>    // 图像编码头文件
#include <opencv2/imgproc/imgproc.hpp>      // OpenCV的图像处理头文件
#include <opencv2/highgui/highgui.hpp>      // OpenCV的图形化显示头文件
#include <geometry_msgs/Twist.h>            // 消息包类型头文件

/* 使用命名空间 */
using namespace cv;
using namespace std;

/* 颜色阈值 */
static int iLowH = 10;
static int iHighH = 40;

static int iLowS = 90;
static int iHighS = 255;

static int iLowV = 1;
static int iHighV = 255;

/* 相当于声明为全局变量 */
geometry_msgs::Twist vel_cmd;   // 速度消息包
ros::Publisher vel_pub;         // 速度发布对象


/* 回调函数 */
void Cam_RGB_Callback(const sensor_msgs::Image msg)
{
    cv_bridge::CvImagePtr cv_ptr;      // OpenCV图像类型指针

    try
    {
        /* 调用toCvCopy()函数将ROS中的图片消息包转换成OpenCV格式的图像对象 */
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        /* 错误提示 */
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    /* 获取OpenCV中最原始的彩色图像 */
    Mat imgOriginal = cv_ptr->image;

    /* 将RGB图片转换成HSV */
    Mat imgHSV;
    vector<Mat> hsvSplit;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

    /* HSV空间做直方图均衡化 */
    split(imgHSV, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);     // 对V值均衡化
    merge(hsvSplit, imgHSV);

    /* 使用阈值范围进行二值化 */
    Mat imgThresholded;
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);

    /* 开操作即腐蚀，去除噪声 */
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);

    /* 闭操作，连接一些连通域 */
    morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

    /* 遍历二值化后的图像数据 */
    int nTargetX = 0;
    int nTargetY = 0;
    int nPixCount = 0;
    int nImgWidth = imgThresholded.cols;
    int nImgHeight = imgThresholded.rows;
    int nImgChannels = imgThresholded.channels();
    printf("横向宽度= %d 纵向宽度= %d \n", nImgWidth, nImgHeight);
    for (int y = 0; y < nImgHeight; y ++)
    {
        for (int x = 0; x < nImgWidth; x ++)
        {
            if (imgThresholded.data[y*nImgWidth + x] == 255)
            {
                nTargetX += x;
                nTargetY += y;
                nPixCount ++;
            }
        }
    }

    if (nPixCount > 0)
    {
        /* 物体质心画十字标记 */
        nTargetX /= nPixCount;
        nTargetY /= nPixCount;
        printf("颜色质心坐标( %d, %d ) 点数 = %d\n", nTargetX, nTargetY, nPixCount);
        /* 画坐标 */
        Point line_begin = Point(nTargetX - 10, nTargetY);
        Point line_end = Point(nTargetX + 10, nTargetY);
        line(imgOriginal, line_begin, line_end, Scalar(255, 0, 0));
        line_begin.x = nTargetX;
        line_begin.y = nTargetY + 10;
        line_end.x = nTargetX;
        line_end.y = nTargetY + 10;
        line(imgOriginal, line_begin, line_end, Scalar(255, 0, 0));

        /* PID计算机器人运动速度 */
        float fVelFoward = (nImgHeight / 2 - nTargetY) * 0.002;
        float fVelTurn = (nImgWidth / 2 - nTargetX) * 0.003;
        vel_cmd.linear.x = fVelFoward;
        vel_cmd.linear.y = 0;
        vel_cmd.linear.z = 0;
        vel_cmd.angular.x = 0;
        vel_cmd.angular.y = 0;
        vel_cmd.angular.z = fVelTurn;
    }
    else
    {
        printf("目标颜色消失...\n");
        vel_cmd.linear.x = 0;
        vel_cmd.linear.y = 0;
        vel_cmd.linear.z = 0;
        vel_cmd.angular.x = 0;
        vel_cmd.angular.y = 0;
        vel_cmd.angular.z = 0;
    }

    /* 发送速度 */
    vel_pub.publish(vel_cmd);
    printf("机器人运动速度(linear.x = %.2f, angular.z = %.2f)\n", vel_cmd.linear.x, vel_cmd.angular.z);

    /* 显示处理结果 */
    imshow("RGB", imgOriginal);
    imshow("Result", imgThresholded);
    cv::waitKey(1);
}

int main(int argc, char** argv)
{
    /* 初始化ROS */
    ros::init(argc, argv, "cv_follow_node");

    /* 订阅相机话题 */
    ros::NodeHandle nh;
    ros::Subscriber rgb_sub = nh.subscribe("/kinect2/qhd/image_color_rect", 1, Cam_RGB_Callback);
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 30);

    /* 生成图像显示和参数调节的窗口 */
    namedWindow("Threshold", WINDOW_AUTOSIZE);

    /* 生成滑杆控件 */
    createTrackbar("LowH", "Threshold", &iLowH, 179);       // Hue (0 - 179)
    createTrackbar("HighH", "Threshold", &iHighH, 179);

    createTrackbar("LowS", "Threshold", &iLowS, 255);       // Saturation (0 - 255)
    createTrackbar("HighS", "Threshold", &iHighS, 255);

    createTrackbar("LowV", "Threshold", &iLowV, 255);       // Value (0 - 255)
    createTrackbar("HighV", "Threshold", &iHighV, 255);
    
    /* 图像显示窗口 */
    namedWindow("RGB");
    namedWindow("Result");

    /* 保存程序的持续运行 */
    ros::Rate loop_rate(30);
    while(ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
}
