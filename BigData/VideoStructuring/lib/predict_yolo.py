import cv2
import numpy as np

import model.yolov4.tf as yolo

detector = yolo.YoloV4(
    names_path="./data/darknet/coco.names",
    weights_path="./data/darknet/yolov4.weights",
)

img, boxs = detector.predict(cv2.imread("./data/3.jpg"), detector.classes)

cv2.imshow('img', img)

image_h, image_w, _ = img.shape
for box in boxs:
    coor = np.array(box[:4], dtype=np.int32)
    cv2.imshow("c", img[coor[1]:coor[3], coor[0]:coor[2]])
    # cv2.imshow("a", img[coor[0]:coor[2], coor[1]:coor[3]])
cv2.waitKey(0)
cv2.destroyAllWindows()
