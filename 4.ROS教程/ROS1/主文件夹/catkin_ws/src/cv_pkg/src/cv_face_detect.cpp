#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>            // 转换格式头文件
#include <sensor_msgs/image_encodings.h>    // 图像编码头文件
#include <opencv2/imgproc/imgproc.hpp>      // OpenCV的图像处理头文件
#include <opencv2/highgui/highgui.hpp>      // OpenCV的图形化显示头文件
#include <opencv2/objdetect/objdetect.hpp>  // OpenCV检测头文件

/* 使用命名空间 */
using namespace cv;
using namespace std;

/* 分类器对象 */
static CascadeClassifier face_cascade;

/* Mat对象用于存放黑白图像，输入给分类器 */
static Mat frame_gray;

/* 容器，相当于数组，存放检测结果 */
static vector<Rect> faces;
static vector<Rect>::const_iterator face_iter;  /* 与前面数组配套的迭代器 */

/* 回调函数 */
void callbackRGB(const sensor_msgs::Image msg)
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

    /* 转换成黑白图像 */
    cvtColor(imgOriginal, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    /* 检测人脸,结果存在faces中 */
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 9, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

    /* 在彩色原图上标注人脸位置 */
    if (faces.size() > 0)
    {
        /* 遍历所有人脸 */
        for (face_iter = faces.begin(); face_iter != faces.end(); ++face_iter)
        {
            /* 标注人脸 */
            rectangle(
                imgOriginal,
                Point(face_iter->x, face_iter->y),
                Point(face_iter->x + face_iter->width, face_iter->y + face_iter->height),
                CV_RGB(255, 0, 255),
                2);
        }
        imshow("faces", imgOriginal);
        waitKey(1);
    }
}

/* 主函数 */
int main(int argc, char** argv)
{
    /* 初始化ROS */
    ros::init(argc, argv, "cv_face_detect");

    namedWindow("faces");

    /* 读取人脸特征文件 */
    std::string strLoadFile;
    char const* home = getenv("HOME");  /* 获取主文件夹路径 */
    strLoadFile = home;
    strLoadFile += "/catkin_ws";
    strLoadFile += "/src/wpr_simulation/config/haarcascade_frontalface_alt.xml";    /* 人脸特征模板 */

    /* 加载特征模板 */
    bool res = face_cascade.load(strLoadFile);
    if (res == false)
    {
        ROS_ERROR("fail to load haarcascade_frontalface_alt.xml");
        return 0;
    }

    /* 订阅话题 */
    ros::NodeHandle nh;
    ros::Subscriber rgb_sub = nh.subscribe("/kinect2/qhd/image_color_rect", 1, callbackRGB);

    ros::spin();
    return 0;
}


