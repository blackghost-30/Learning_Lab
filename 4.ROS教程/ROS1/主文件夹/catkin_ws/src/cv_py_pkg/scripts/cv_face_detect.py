#!/usr/bin/env python3
# coding=utf-8

import rospy
import cv2
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError       # 格式转换相关文件

# 回调函数
def Cam_RGB_Callback(msg):
    bridge = CvBridge()         # 图像格式转换器对象
    
    # 转换成OpenCV格式
    cv_image = bridge.imgmsg_to_cv2(msg, "bgr8")

    # 转换为灰度图
    gray_img = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)

    # 创建一个级联分类器，注意第二个横杠后面是用户名
    face_casecade = cv2.CascadeClaaifier(\
        '/home/blackghost/catkin_ws/src/wpb_home/wpb_home_python/config/haarcascade_frontalface_alt.xml'\
        )

    # 加载文件，人脸检测
    face = face_casecade.detectMultiScale(gray_img, 1.3, 5)

    # 遍历人脸
    for (x, y, w, h) in face:
        cv2.rectangle(cv_image, (x, y), (x + w, y + h), (0, 0, 255), 3)
    
    # 显示结果
    cv2.imshow("face window", cv_image)
    cv2.waitKey(1)

# 主函数
if __name__ == "__main__":
    # ROS初始化
    rospy.init_node("cv_face_detect")

    # 订阅相机话题
    rgb_sub = rospy.Subscriber("/kinect2/qhd/image_color_rect", Image, Cam_RGB_Callback, queue_size=1)

    rospy.spin()
