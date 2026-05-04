#include "ros/ros.h"
#include "sensor_msgs/Imu.h"    // 引入消息包头文件
#include "tf/tf.h"              // 引入TF的头文件
#include "geometry_msgs/Twist.h"

ros::Publisher vel_pub;

void IMUCallback(sensor_msgs::Imu msg)
{
    if(msg.orientation_covariance[0] < 0)   // 协方差矩阵判断数据是否有效
        return;
    tf::Quaternion quaternion(          // 将消息包四元数转换为TF的四元数对象
        msg.orientation.x,
        msg.orientation.y,
        msg.orientation.z,
        msg.orientation.w
    );

    double roll, pitch, yaw;        // 用于存放欧拉角结果的变量

    // 将四元数对象转换为矩阵然后再调用API获取欧拉角
    tf::Matrix3x3(quaternion).getRPY(roll, pitch, yaw);
    
    //将弧度的欧拉角转换为角度的欧拉角
    roll = roll*180/M_PI;
    pitch = pitch*180/M_PI;
    yaw = yaw*180/M_PI;

    ROS_INFO("滚转 = %.0f 俯仰 = %.0f 朝向 = %.0f", roll, pitch, yaw);  // 显示欧拉角

    double target_yaw = 90;                     // 目标角度
    double diff_angle = target_yaw - yaw;       // PID的误差
    geometry_msgs::Twist vel_cmd;               // 速度变量
    vel_cmd.angular.z = diff_angle * 0.01;      // 误差控制PID
    vel_cmd.linear.x = 0.1;                     // 向前运动的速度
    vel_pub.publish(vel_cmd);                   // 发布速度话题

}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "imu_node");      // 注册节点

    ros::NodeHandle n;      // 创建大管家对象
    ros::Subscriber imu_sub = n.subscribe("/imu/data", 10, IMUCallback);    // 获取话题订阅对象

    vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::spin();

    return 0;
}
