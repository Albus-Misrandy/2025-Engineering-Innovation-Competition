"""
Author: Albus.Misrandy
"""
import cv2
import os

# 创建文件夹（如果不存在的话）
save_dir = 'captured_images'
if not os.path.exists(save_dir):
    os.makedirs(save_dir)

# 打开摄像头
cap = cv2.VideoCapture(1)
if not cap.isOpened():
    print("无法打开摄像头")
    exit()

print("按 'c' 键拍照并保存，按 'ESC' 键退出")

image_count = 0

while True:
    ret, frame = cap.read()
    ret1, frame1 = cap.read()
    if not ret:
        print("无法获取帧")
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 可选：增加对比度或进行阈值化处理
    _, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

    # 检测棋盘格角点
    # 尝试增加一些标志来帮助检测
    ret00, corners = cv2.findChessboardCorners(thresh, (9, 6),
                                             flags=cv2.CALIB_CB_ADAPTIVE_THRESH + cv2.CALIB_CB_NORMALIZE_IMAGE)

    cv2.drawChessboardCorners(frame, (9, 6), corners, ret00)

    print(ret00)

    # cv2.waitKey(1)


    cv2.imshow("Camera", frame)

    key = cv2.waitKey(1) & 0xFF

    # 按下 'c' 键拍照并保存
    if key == ord('c'):
        image_count += 1
        img_name = os.path.join(save_dir, f"captured_image_{image_count}.jpg")
        cv2.imwrite(img_name, frame1)
        print(f"图片已保存到: {img_name}")

    # 按下 'ESC' 键退出
    elif key == 27:
        break

# 释放摄像头并关闭所有窗口
cap.release()
cv2.destroyAllWindows()
