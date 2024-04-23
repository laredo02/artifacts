
import numpy as np
from tensorflow import keras
from tensorflow.keras import layers

num_classes = 10 # 10 clases que corresponden con los 10 dígitos que queremos reconocer
input_shape = (28, 28, 1) # formato de la entrada que vamos a utilizar en el modelo. Se trata de imágenes grayscale de 28x28

(x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data() # Cargamos el dataset que ofrece keras para entrenar un modelo MNIST (por un lado los datos de entrenamiento y por otro los de prueba para verificar el correcto funcionamiento)
x_test = x_test.astype("float32") / 255
x_train = np.expand_dims(x_train, -1) # añadimos una dimensión a los datos de entrada
x_test = np.expand_dims(x_test, -1)
y_train = keras.utils.to_categorical(y_train, num_classes) # Convertimos los vectores de clase en matrices binarias es decir, pasamos los vectores de clase resultantes a vectores binarios para facilitar el trabajo de comprobación
y_test = keras.utils.to_categorical(y_test, num_classes)

model = keras.Sequential(                                               # Modelo para el MNIST
    [
        keras.Input(shape=input_shape),                                 # Tamaño de la entrada 28x28x1
        layers.Conv2D(32, kernel_size=(3, 3), activation="relu"),       # Primera capa convolucional con activación RELU
        layers.MaxPooling2D(pool_size=(2, 2)),                          # 
        layers.Conv2D(64, kernel_size=(3, 3), activation="relu"),
        layers.MaxPooling2D(pool_size=(2, 2)),
        layers.Flatten(),                                               # "Aplana la entrada", es decir, convierte (2, 3) en (6)
        layers.Dropout(0.5),                                            # Aplica valor 0 de manera aleatoria a los datos de entrada para prevenir overfitting
        layers.Dense(num_classes, activation="softmax"),                # Capa densa (Todas las entradas conectadas a todas las salidas). Al ser la capa final, contiene num_clases elementos de salida
    ]
)
#model.summary() # Imrpimir un resumen de la red

batch_size = 128 # elementos cogidos de 128 en 128
epochs = 15 # entrenaremos el modelo con 15 iteraciones sobre los datos de entrenamiento
model.compile(loss="categorical_crossentropy", optimizer="adam", metrics=["accuracy"])
model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, validation_split=0.1)

score = model.evaluate(x_test, y_test, verbose=0) # Evaluamos la precisión del modelo
print("Test loss:", score[0]) # Fallos
print("Test accuracy:", score[1]) # Precisión

model.save("model.h5") # Guardamos el modelo para poder utilizarlo en la aplicación final con mediapipe

