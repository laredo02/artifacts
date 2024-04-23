
import cv2
import mediapipe as mp
import numpy as np
from tensorflow import keras
from tensorflow.keras import layers
from keras.models import load_model
 
# Inicialización de mediapipe, librería que realizará el trabajo de localizar los diferentes dedos
mpHands = mp.solutions.hands
hands = mpHands.Hands(
    static_image_mode=False,
    model_complexity=1,
    min_detection_confidence=0.75,
    min_tracking_confidence=0.75,
    max_num_hands=2)
Draw = mp.solutions.drawing_utils

# Inicializamos la imagen que posteriormente pasaremos par ser analizada por el modelo MNIST
wimg = np.zeros([400, 400, 1], dtype=np.uint8)
wimg.fill(0)

draw = False
# finger_trail = []
cap = cv2.VideoCapture(0)
while True:
    _, frame = cap.read()
    frame = cv2.flip(frame, 1) # Le damos la vuelta para ver la imagen como si de un espejo se tratara
    frameRGB = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB) # Convertir la imagen a RGB para que mediapipe pueda trabajar con ella
    # El siguiente paso es dibujar un rectángulo sobre el que será posible dibujar con la mano
    # Se tratará de un rectangulo del punto [0, 0] al punto [400, 400] de manera que sobrará un poco de hueco por el margen derecho 
    # y por el inferior. Esto facilitará la detección de la mano asumiendo que el usuario es diestro ya que máximiza la superficie
    # sobre la que se puede escribir con el dedo índice. La imagen será cuadrada para que al reescalarla no haya problema al interactuar con el modelo MNIST ya que este modelo concreto admite imagenes de 28x28.
    frame = cv2.rectangle(frame, (0, 0), (400, 400), (0, 0, 255), 1) # dibujamos sobre la imagen el rectangulo sobre el que se podra dibujar 
    Process = hands.process(frameRGB) # Procesar la imagen con mediapipe para obtener los "landmarks" de las manos
    landmarkList = []
    if Process.multi_hand_landmarks:
        for handlm in Process.multi_hand_landmarks:
            for _id, landmarks in enumerate(handlm.landmark):
                height, width, color_channels = frame.shape # Guardar altura, anchura y profundidad de la imagen
                x, y = int(landmarks.x*width), int(landmarks.y*height)
                landmarkList.append([_id, x, y]) # Añadir landmarks
            Draw.draw_landmarks(frame, handlm, # Dibujar landmarks
                                mpHands.HAND_CONNECTIONS)
    # If landmarks list is not empty
    if landmarkList != []:
        #x_1, y_1 = landmarkList[4][1], landmarkList[4][2] # Almacenar coordenadas del Pulgar
        x, y = landmarkList[8][1], landmarkList[8][2] # Almacenar coordenadas del índice
        if draw:
            cv2.circle(wimg, (x, y), 20, (255, 255, 255), thickness=-1) # Si nos encontramos en modo dibujar: dibujar un circulo en la posición del dedo índice
            # finger_trail.append((x, y))
            # for i in finger_trail:
                # cv2.circle(frame, (i[0], i[1]), 20, (0, 0, 255), thickness=-1) tambíen podríamos dibujar el trazado en la propia captura de la cámara
        cv2.circle(frame, (x, y), 20, (0, 0, 255), cv2.FILLED) # Dibujar el puntero en el dedo con el que podremos pintar

    cv2.imshow("MNIST Image", wimg);
    cv2.imshow('Camera Capture', frame)
    key = cv2.waitKey(1)
    if key & 0xff == ord('q'): # Salir de la aplicación
        exit(0)
    if key & 0xff == ord('m'): # Salir del bucle y aplicar el modelo de IA a la imagen actual
        break
    elif key & 0xff == ord('d') and draw == False: # Si se pulsa la letra d y no estamos en modo dibujar, entraremos en modo dibujar
        draw = True
    elif key & 0xff == ord('d') and draw == True: # Si se pulsa la letra d y estamos en modo dubujar saldremos del mismo
        draw = False

# Preprocesado de la imagen antes de pasarsela al modelo MNIST
wimg = cv2.resize(wimg, (28, 28)) # El modelo admite imagenes de 28x28 ya que mi humilde ordenador no puede entrenar con imagenes de más resolucion en tiempos razonables. Además keras ofrece el dataset en su libreria
img_arr = np.array(wimg)
img_arr = img_arr.astype("float32")/255 # Normalizamos la imagen para que sea compatioble con el modelo que hemos entrenado
img_arr = np.expand_dims(img_arr, axis=-1) # jugamos con las dimensiones para que el modelo admita la imagen
arr = np.array([img_arr])
cv2.imshow("MNIST Image Rescaled", wimg); # Mostrar la imagen que se va a pasar al modelo
cv2.waitKey(0);

model = load_model('mnist_model/model.h5') # Cargar el modelo del archivo model.h5
prediction = model.predict(arr) # Generar la predicción
print("prediccion = ", prediction);
prediction = np.argmax(prediction, axis=1)[:5] # Seleccionar la clase que ha elegido el modelo
print("prediction = ", prediction) # Imprimir la predicción



