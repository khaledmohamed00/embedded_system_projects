#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 21 23:22:24 2017

@author: khaled
"""

# Artificial Neural Network

# Installing Theano
# pip install --upgrade --no-deps git+git://github.com/Theano/Theano.git

# Installing Tensorflow
# pip install tensorflow

# Installing Keras
# pip install --upgrade keras

# Part 1 - Data Preprocessing

# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import cv2
# Importing the dataset


def create_img_dataset(image, width, height, block_width, block_height):
    X = []
    img_grey = cv2.imread(image, 0)
    img = np.array(img_grey)
    cv2.imwrite('lena_before.png',img)
    for i in range(0, height - block_height + 1, block_height):
        for j in range(0, width - block_width + 1, block_width):
            X.append(img[i:i + block_height, j:j + block_width].ravel())
    X = np.array(X)
    return X



def recompose_image(Y_Hat, width, height, block_width, block_height):
    no_blocks_width = width // block_width
    no_blocks_height = height // block_height
    no_blocks = no_blocks_width * no_blocks_height
    recomposed_img_1D = []
    recomposed_img = []
    for i in range(0, no_blocks):
        block = np.reshape(Y_Hat[i], (block_height, block_width))
        recomposed_img.append(block)
    recomposed_img = np.array(recomposed_img)
    for row in range(no_blocks_height, no_blocks + 1, no_blocks_height):
        if row == no_blocks_height:
            old_row = 0
        for i in range(0, block_height):
            for j in range(old_row, row):
                recomposed_img_1D.append(recomposed_img[j][i])
        old_row = row
    recomposed_img_1D = np.array(recomposed_img_1D)
    recomposed_img_1D = recomposed_img_1D.ravel()
    recomposed_img = np.reshape(recomposed_img_1D, (height, width))
    return recomposed_img



#data = create_img_dataset('wallpapers2/a53.tif',64,64,4,4)
data = create_img_dataset('lena.tif',64,64,4,4)
data=data/255






'''

dataset = pd.read_csv('Churn_Modelling.csv')
X = dataset.iloc[:, 3:13].values
y = dataset.iloc[:, 13].values

# Encoding categorical data
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
labelencoder_X_1 = LabelEncoder()
X[:, 1] = labelencoder_X_1.fit_transform(X[:, 1])
labelencoder_X_2 = LabelEncoder()
X[:, 2] = labelencoder_X_2.fit_transform(X[:, 2])
onehotencoder = OneHotEncoder(categorical_features = [1])
X = onehotencoder.fit_transform(X).toarray()
X = X[:, 1:]

# Splitting the dataset into the Training set and Test set
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 0)

# Feature Scaling
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
X_train = sc.fit_transform(X_train)
X_test = sc.transform(X_test)
'''
# Part 2 - Now let's make the ANN!

# Importing the Keras libraries and packages
import keras
from keras.models import Sequential
from keras.layers import Dense
from keras import backend as K
from keras.models import Model

# Initialising the ANN
classifier = Sequential()

# Adding the input layer and the first hidden layer
classifier.add(Dense(units = 15, kernel_initializer = 'uniform', activation = 'relu', input_dim = 16))

# Adding the second hidden layer

classifier.add(Dense(units = 14, kernel_initializer = 'uniform', activation = 'relu'))

# Adding the second hidden layer
classifier.add(Dense(units = 12, kernel_initializer = 'uniform', activation = 'relu'))
# Adding the second hidden layer
classifier.add(Dense(units = 14, kernel_initializer = 'uniform', activation = 'relu'))

# Adding the output layer
classifier.add(Dense(units = 16, kernel_initializer = 'uniform', activation = 'sigmoid'))

# Compiling the ANN
classifier.compile(optimizer = 'adam', loss = 'binary_crossentropy', metrics = ['accuracy'])

# Fitting the ANN to the Training set
classifier.fit(data, data, batch_size = 1, epochs = 100)

# Part 3 - Making predictions and evaluating the model

# Predicting the Test set results

#lol=np.reshape(X_test[1],(1,11))
y_pred = classifier.predict(data)
#y_pred = classifier.predict(X_test)

#y_pred = (y_pred > 0.5)

# Making the Confusion Matrix

#from sklearn.metrics import confusion_matrix
#cm = confusion_matrix(y_test, y_pred)
#from keras.models import Model

from keras import backend as Ke

inp = classifier.input
#inp=X_test[0]                                           # input placeholder
outputs = [layer.output for layer in classifier.layers]          # all layer outputs
functors = [Ke.function([inp]+ [Ke.learning_phase()], [out]) for out in outputs]  # evaluation functions

# Testing
input_shape=1
test = data#np.random.random(input_shape)[np.newaxis,...]
layer_outs = [func([test, 1.]) for func in functors]
#np.array(layer_outs[0]).shape
#recomposed_image = recompose_image(np.reshape(np.array(layer_outs[3]),(256,12)),64,48,4,3)
recomposed_image = recompose_image(y_pred,64,64,4,4)
cv2.imshow('Recomposed Image', recomposed_image)
cv2.waitKey(0)
cv2.imwrite('01.png',recomposed_image*255)
cv2.destroyAllWindows()
#lol=classifier.layers[2].output
#lol
#outputs    = [layer.output for layer in Model.layers]  
#print (layer_outs)







'''
import cv2
cap = cv2.VideoCapture(0)

while(cap.isOpened()):  # check !
    # capture frame-by-frame
    ret, frame = cap.read()

    if ret: # check ! (some webcam's need a "warmup")
        # our operation on frame come here
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Display the resulting frame
        cv2.imshow('frame', gray)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
 '''       