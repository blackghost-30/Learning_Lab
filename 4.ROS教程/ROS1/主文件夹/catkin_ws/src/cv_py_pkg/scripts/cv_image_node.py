#!/usr/bin/env python3
# coding=utf-8

import rospy
import cv2
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError       # 格式转换相关文件

# 回调函数
def Cam_RGB_Callback(msg):
    bridge = CvBridge()         # 图像格式转换器对象

    # 图像格式转换
    try:
        cv_image = bridge.imgmsg_to_cv2(msg, "bgr8")
    except CvBridgeError as e:
        rospy.logerr("格式转换错误：%s", e)
        return
    
    # 弹出窗口进行显示
    cv2.imshow("RGB", cv_image)
    cv2.waitKey(1)


# 主函数
if __name__ == "__main__":
    # ROS初始化
    rospy.init_node("cv_image_node")

    # 订阅相机话题
    rgb_sub = rospy.Subscriber("/kinect2/qhd/image_color_rect", Image, Cam_RGB_Callback, queue_size=10)

    rospy.spin()