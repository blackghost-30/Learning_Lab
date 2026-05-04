#!/usr/bin/env python3
# coding=utf-8

import rospy
from nav_msgs.msg import OccupancyGrid  # 引入消息类型

if __name__ == "__main__":
    rospy.init_node("map_pub_node") # 注册节点

    pub = rospy.Publisher("/map", OccupancyGrid, queue_size=10) # 获取发布对象

    rate = rospy.Rate(1)

    while not rospy.is_shutdown():
        msg = OccupancyGrid()   # 定义发布数据变量

        # 赋值header数据
        msg.header.frame_id = "map"
        msg.header.stamp = rospy.Time.now()

        # 赋值info数据
        msg.info.origin.position.x = 0
        msg.info.origin.position.y = 0
        msg.info.resolution = 1.0
        msg.info.width = 4
        msg.info.height = 2

        # 赋值data数据
        msg.data = [0]*4*2
        msg.data[0] = 100
        msg.data[1] = 100
        msg.data[2] = 0
        msg.data[3] = -1

        pub.publish(msg)    # 发布数据
        rate.sleep()