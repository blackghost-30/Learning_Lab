#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>              /* MoveBaseAction的消息包格式 */
#include <actionlib/client/simple_action_client.h>      /* 简单的Action客户端模式 */

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;   /* 将客户端类型重定义 */

int main(int argc, char** argv)
{
    ros::init(argc, argv, "nav_client");

    /* 生成客户端对象 */
    MoveBaseClient ac("move_base", true);   /* true表示自动阻塞等待结果 */

    while(!ac.waitForServer(ros::Duration(5.0)))    /* 等待导航启动 */
    {
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    /* 目的地信息 */
    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id = "amp";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = -3.0;
    goal.target_pose.pose.position.y = 2.0;
    goal.target_pose.pose.orientation.w = 1.0;

    ROS_INFO("Sending goal");

    /* 发送目标 */
    ac.sendGoal(goal);

    /* 等待结果 */
    ac.waitForResult();

    /* 查询返回i状态 */
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Mission complete!");
    else
        ROS_INFO("Mission failed ...");

    return 0;
}