#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>            // 转换格式头文件
#include <sensor_msgs/image_encodings.h>    // 图像编码头文件
#include <opencv2/imgproc/imgproc.hpp>      // OpenCV的图像处理头文件
#include <opencv2/highgui/highgui.hpp>      // OpenCV的图形化显示头文件

using namespace cv;     /* 使用命名空间 */

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

    /* 定义OpenCV自己的图像格式，将cv_ptr的image取出来并显示 */
    Mat imgOriginal = cv_ptr->image;
    imshow("RGB", imgOriginal);
    waitKey(1);
}

int main(int argc, char** argv)
{
    /* 初始化ROS */
    ros::init(argc, argv, "cv_image_node");

    /* 订阅相机话题 */
    ros::NodeHandle nh;
    ros::Subscriber rgb_sub = nh.subscribe("/kinect2/qhd/image_color_rect", 1, Cam_RGB_Callback);

    /* 图像显示窗口 */
    namedWindow("RGB");
    ros::spin();
}