import cv2
import numpy as np

# 均值滤波
def mean_filter(img, K_size=3):
    H, W, C = img.shape
    # zero padding
    pad = K_size // 2
    out = np.zeros((H + pad * 2, W + pad * 2, C), dtype=np.float)
    out[pad: pad + H, pad: pad + W] = img.copy().astype(np.float)
    tmp = out.copy()

    # 滤波过程
    for y in range(H):
        for x in range(W):
            for c in range(C):
                out[pad + y, pad + x, c] = np.mean(tmp[y: y + K_size, x: x + K_size, c])

    out = out[pad: pad + H, pad: pad + W].astype(np.uint8)

    return out

# 读取图像
img = cv2.imread("imori.jpg")

# 均值滤波
out = mean_filter(img, K_size=3)

# 保存结果
cv2.imwrite("out.jpg", out)
