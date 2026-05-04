#include <ros/ros.h>
#include <std_msgs/String.h>    // 目标航点名称为字符串格式

void NavResultCallback(const std_msgs::String &msg)
{
    ROS_WARN("[NavResultCallback] %s", msg.data.c_str());
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "wp_node");       // 初始化ros

    ros::NodeHandle n;      // 节点对象

    ros::Publisher nav_pub = n.advertise<std_msgs::String>("/waterplus/navi_waypoint", 10);     // 发布话题
    ros::Subscriber res_sub = n.subscribe("/waterplus/navi_result", 10, NavResultCallback);     // 订阅话题

    sleep(1);

    std_msgs::String nav_msg;
    nav_msg.data = "1";
    nav_pub.publish(nav_msg);

    ros::spin();

    return 0;
}