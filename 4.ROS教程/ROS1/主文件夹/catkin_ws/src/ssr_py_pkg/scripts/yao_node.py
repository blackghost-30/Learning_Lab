#!/usr/bin/env python3
#coding=utf-8

import rospy
from std_msgs.msg import String

if __name__ == "__main__":
    rospy.init_node("yao_node")
    rospy.logwarn("过去生于未来")

    pub = rospy.Publisher("gie_gie_dai_wo", String, queue_size=10)

    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        rospy.loginfo("我要开始刷屏了")

        msg = String()
        msg.data = "求上车++++"
        pub.publish(msg)
        rate.sleep()