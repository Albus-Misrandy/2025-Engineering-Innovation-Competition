"""
Author: Albus.Misrandy
"""
import cv2
import numpy as np
import glob
import os

# 准备标定板的真实世界坐标，假设棋盘格的每个方格大小为 20mm (0.02m)
chessboard_size = (9, 6)  # 8x8的棋盘格
square_size = 20.0 / 1000  # 每个格子的实际大小为 20mm (转为米单位)

# 标定板角点的世界坐标，假设棋盘格平面为 z=0
obj_points = []  # 三维点
img_points = []  # 二维点

# 构建棋盘格的真实世界坐标 (x, y, 0)，每个角点的坐标为 (i * square_size, j * square_size, 0)
objp = np.zeros((chessboard_size[0] * chessboard_size[1], 3), np.float32)
objp[:, :2] = np.mgrid[0:chessboard_size[0], 0:chessboard_size[1]].T.reshape(-1, 2)
objp *= square_size  # 将实际尺寸乘以格子的边长

# 加载所有棋盘格图像文件
images = glob.glob('captured_images/*.jpg')  # 这里是你存放棋盘格图像的文件夹路径

# 确保路径正确
# image_folder = "D:/PycharmProjects/8011Vision/Camera Calibration/captured_images"
# image_files = glob.glob(os.path.join(image_folder, "*.jpg"))

if not images:
    print("⚠️ Error: No images found in the folder!")
    exit()

print(f"✅ Found {len(images)} images. Processing...")
print(images)

for image_path in images:
    # 读取图片
    img = cv2.imread(image_path)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # 检测棋盘格角点
    ret, corners = cv2.findChessboardCorners(gray, chessboard_size, None)

    # 如果找到角点
    if ret:
        img_points.append(corners)  # 保存角点的二维坐标
        obj_points.append(objp)  # 保存棋盘格角点的三维坐标

        # 可选：画出角点并显示
        cv2.drawChessboardCorners(img, chessboard_size, corners, ret)
        cv2.imshow('Chessboard', img)
        cv2.waitKey(500)

# 关闭所有窗口
cv2.destroyAllWindows()
print(len(obj_points))
# 进行标定
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(obj_points, img_points, gray.shape[::-1], None, None)

# 输出标定结果
print("标定结果：")
print("相机内参矩阵：")
print(mtx)
print("畸变系数：")
print(dist)

# 如果你知道摄像头是无畸变的，你可以将畸变系数设为零并保存
# dist = np.zeros((5, 1))  # 无畸变的情况下，畸变系数为零

# 将标定结果保存到文件
# np.savez("camera_calibration.npz", mtx=mtx, dist=dist, rvecs=rvecs, tvecs=tvecs)

# # 校正一张图像（示例）
# img = cv2.imread('captured_images/test_image.jpg')  # 你可以选择任意一张图像
# h, w = img.shape[:2]
# new_mtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (w, h), 1, (w, h))
# dst = cv2.undistort(img, mtx, dist, None, new_mtx)
#
# # 显示校正后的图像
# cv2.imshow('Undistorted Image', dst)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
