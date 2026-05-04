#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>     // 引入消息类型

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "mao_pub_node");  // 注册节点
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<nav_msgs::OccupancyGrid>("/map", 10);  //获取发布对象

    ros::Rate r(1); // 速率控制对象

    while(ros::ok())
    {
        nav_msgs::OccupancyGrid msg;    // 定义发布消息变量

        // 赋值消息变量的header数据
        msg.header.frame_id = "map";
        msg.header.stamp = ros::Time::now();

        // 赋值消息变量的info数据
        msg.info.origin.position.x = 0;
        msg.info.origin.position.y = 0;
        msg.info.resolution = 1.0;
        msg.info.width = 4;
        msg.info.height = 2;

        // 赋值消息变量的data数据
        msg.data.resize(4*2);
        msg.data[0] = 100;
        msg.data[1] = 100;
        msg.data[2] = 0;
        msg.data[3] = -1;

        pub.publish(msg);   // 发布消息数据
        r.sleep();
    }
    return 0;
}