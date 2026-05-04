#!/usr/bin/env python3
#coding=utf-8

import rospy
from std_msgs.msg import String
from qq_msgs.msg import Carry

def chao_callback(msg):
    rospy.logwarn(msg.grade)
    rospy.logwarn(str(msg.star)+'星')
    rospy.loginfo(msg.data)

def yao_callback(msg):
    rospy.logwarn(msg.data)

if __name__ == "__main__":
    rospy.init_node("ma_node")

    sub = rospy.Subscriber("kuai_shang_che_kai_hei_qun", Carry, chao_callback, queue_size=10)

    sub2 = rospy.Subscriber("gie_gie_dai_wo", Carry, yao_callback, queue_size=10)

    rospy.spin()
