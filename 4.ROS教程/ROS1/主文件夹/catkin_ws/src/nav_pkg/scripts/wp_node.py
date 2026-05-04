#!/usr/bin/env python3
# coding=utf-8

import rospy
from std_msgs.msg import String

def NavResultCallback(msg):
    rospy.logwarn("导航结果 = %s", msg.data)

if __name__ == "__main__":
    rospy.init_node("wp_node")

    navi_pub = rospy.Publisher("/waterplus/navi_waypoint", String, queue_size=10)
    res_sub = rospy.Subscriber("/waterplus/navi_result", String, NavResultCallback, queue_size=10)

    rospy.sleep(1)

    navi_msg = String()
    navi_msg.data = '1'

    navi_pub.publish(navi_msg)

    rospy.spin()
    