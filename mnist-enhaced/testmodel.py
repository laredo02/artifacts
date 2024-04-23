
import cv2 as cv
import numpy as np
from tensorflow import keras
from tensorflow.keras import layers
from keras.models import load_model

draw = False
lastX = 0
lastY = 0

wimg = np.zeros([512, 512, 1], dtype=np.uint8)
wimg.fill(0)

def drawCircle(event, x, y, flags, param):
    global draw, lastX, lastY
    if (event == cv.EVENT_LBUTTONDOWN):
        draw = True
    elif (event == cv.EVENT_MOUSEMOVE):
        if (draw == True):
            cv.line(wimg, (lastX, lastY), (x, y), (255, 255, 255), 30) # cv.circle(wimg, (x, y), 10, (0, 0, 0), -1)
    elif (event == cv.EVENT_LBUTTONUP):
        draw = False
    lastX = x
    lastY = y

cv.namedWindow(winname = "window")
cv.setMouseCallback("window", drawCircle)


while True:
    cv.imshow("window", wimg)
    if (cv.waitKey(10) & 0xFF == 27):
        break;

# Aplicar las transformaciones necesarias para poder introducir la imagen en el modelo MNIST
img = cv.resize(wimg, (28, 28))
cv.imshow("img", img)
cv.waitKey(0)
# img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
img_arr = np.array(img)
img_arr = np.expand_dims(img_arr, axis=-1)
arr = np.array([img_arr])


model = load_model('mnist_model/model.h5')
prediction = model.predict(arr)
prediction = np.argmax(prediction, axis=1)[:5]
print("prediction = ", prediction)
