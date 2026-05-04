#!/usr/bin/env python3
# coding=utf-8

import rospy
import cv2
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError       # 格式转换相关文件

# 范围阈值
hue_min = 10
hue_max = 40
satu_min = 90
satu_max = 255
val_min = 1
val_max = 255


# 滑杆事件的回调函数
def nothing(x):
    pass


# 节点的回调函数
def Cam_RGB_Callback(msg):
    # 声明为全局变量，避免函数内部当成局部变量
    global hue_min, hue_max, satu_min, satu_max , val_min , val_max

    bridge = CvBridge()         # 图像格式转换器对象

    # 图像格式转换
    try:
        cv_image = bridge.imgmsg_to_cv2(msg, "bgr8")
    except CvBridgeError as e:
        rospy.logerr("格式转换错误：%s", e)
        return
    
    # RGB图片转换成HSV
    hsv_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2HSV)

    # 在HSV空间做均衡化
    h, s, v = cv2.split(hsv_image)
    v = cv2.equalizenHist(v)
    hsv_image = cv2.merge([h, s, v])

    # 二值化
    th_image = cv2.inRange(hsv_image, (hue_min, satu_min, val_min), (hue_max, satu_max, val_max))

    # 开操作去除噪点
    element = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
    th_image = cv2.morphologyEx(th_image, cv2.MORPH_OPEN, element)

    # 闭操作
    th_image = cv2.morphologyEx(th_image, cv2.MORPH_CLOSE, element)

    # 遍历处理后的图像
    target_x, target_y, pix_count = 0, 0, 0
    image_height, image_width = th_image.shape[:2]
    for y in range(image_height):
        for x in range(image_width):
            if th_image[y, x] == 255:
                target_x += x
                target_y += y
                pix_count += 1
    if pix_count > 0:
        target_x //= pix_count
        target_y //= pix_count
        print(f"颜色质心坐标({target_x}, {target_y}) 点数 = {pix_count}")
        # 画作标
        cv2.line(cv_image, (target_x - 10, target_y), (target_x + 10, target_y), (255, 0, 0), 2)
        cv2.line(cv_image, (target_x, target_y - 10), (target_x, target_y + 10), (255, 0, 0), 2)
    else:
        print("目标颜色消失...")

    # 显示主要图像
    cv2.imshow("RGB", cv_image)
    cv2.imshow("HSV", hsv_image)
    cv2.imshow("Result", th_image)
    cv2.waitKey(5)


# 主函数
if __name__ == "__main__":
    # ROS初始化
    rospy.init_node("cv_hsv_node")

    # 订阅相机话题
    rgb_sub = rospy.Subscriber("/kinect2/qhd/image_color_rect", Image, Cam_RGB_Callback, queue_size=10)

    # 添加生成滑杆控件,最后一个参数是滑杆的回调函数
    cv2.namedWindow("Threshold")
    cv2.createTrackbar("hue_min", "Threshold", hue_min, 179, nothing)       # Hue (0 - 179)
    cv2.createTrackbar("hue_max", "Threshold", hue_max, 179, nothing)

    cv2.createTrackbar("satu_min", "Threshold", satu_min, 255, nothing)     # Saturation (0 - 255)
    cv2.createTrackbar("satu_max", "Threshold", satu_max, 255, nothing)

    cv2.createTrackbar("val_min", "Threshold", val_min, 255, nothing)       # Value (0 - 255)
    cv2.createTrackbar("val_max", "Threshold", val_max, 255, nothing)

    # 生成窗口
    cv2.namedWindow("RGB")
    cv2.namedWindow("HSV")
    cv2.namedWindow("Result")

    rate = rospy.Rate(30)

    # 这里统一处理滑杆数据，所以滑杆回调函数什么都不做
    while not rospy.is_shutdown():
        hue_min = cv2.getTrackbarPos("hue_min", "Threshold")
        hue_max = cv2.getTrackbarPos("hue_max", "Threshold")
        satu_min = cv2.getTrackbarPos("satu_min", "Threshold")
        satu_max = cv2.getTrackbarPos("satu_max", "Threshold")
        val_min = cv2.getTrackbarPos("val_min", "Threshold")
        val_max = cv2.getTrackbarPos("val_max", "Threshold")

        rate.sleep()

    cv2.destroyAllWindows()