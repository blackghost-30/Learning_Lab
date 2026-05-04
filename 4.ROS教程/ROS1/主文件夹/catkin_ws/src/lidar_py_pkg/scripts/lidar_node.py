#!/usr/bin/env python3
#coding=utf-8

import rospy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist

count = 0

def LidarCallback(msg):
    global vel_pub
    global count
    dist = msg.ranges[180]
    rospy.loginfo("前方测距 range[180] = %f 米", dist)
    
    if count > 0:
        count = count - 1
        return
    
    vel_cmd = Twist()
    if dist < 1.5:
        vel_cmd.angular.z = 0.3
    else:
        vel_cmd.linear.x = 0.05
    vel_pub.publish(vel_cmd)

if __name__ == "__main__":
    rospy.init_node("lidar_node")
    lidar_sub = rospy.Subscriber("/scan", LaserScan, LidarCallback, queue_size=10)
    vel_pub = rospy.Publisher("/cmd_vel", Twist, queue_size=10)
    rospy.spin()