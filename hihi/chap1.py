import cv2
import numpy as np

img = cv2.imread("Resources/teste.png")
print(img.shape)


imgResize = cv2.resize(img, (300,200))
cv2.imshow("Visao", img)
cv2.imshow("Visao2", imgResize)
cv2.waitKey(0)