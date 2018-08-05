# Artificial Neural Network



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



data = create_img_dataset('lena.png',64,64,4,4)
#data = create_img_dataset('lena-std.png',512,512,4,4)
data=data/255







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
classifier.add(Dense(units = 14, kernel_initializer = 'uniform', activation = 'relu', input_dim = 16))

# Adding the second hidden layer
#classifier.add(Dense(units = 12, kernel_initializer = 'uniform', activation = 'relu'))

# Adding the second hidden layer

#classifier.add(Dense(units = 14, kernel_initializer = 'uniform', activation = 'relu'))

# Adding the second hidden layer
classifier.add(Dense(units = 12, kernel_initializer = 'uniform', activation = 'sigmoid'))
# Adding the second hidden layer
#classifier.add(Dense(units = 14, kernel_initializer = 'uniform', activation = 'relu'))

# Adding the output layer
classifier.add(Dense(units = 16, kernel_initializer = 'uniform', activation = 'sigmoid'))

# Compiling the ANN
classifier.compile(optimizer = 'adam', loss = 'binary_crossentropy', metrics = ['accuracy'])

# Fitting the ANN to the Training set
classifier.fit(data, data, batch_size = 16, epochs = 1000)

# Part 3 - Making predictions and evaluating the model

# Predicting the Test set results

#lol=np.reshape(X_test[1],(1,11))
y_pred = classifier.predict(data)


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
#recomposed_image = recompose_image(np.reshape(np.array(layer_outs[1]),(256,12)),64,48,4,3)
#recomposed_image = recompose_image(y_pred,64,64,4,4)
recomposed_image = recompose_image(np.reshape(np.array(layer_outs[1]),(16384,12)),512,384,4,3)
recomposed_image = recompose_image(y_pred,512,512,4,4)
cv2.imshow('Recomposed Image', recomposed_image)
cv2.waitKey(0)
cv2.imwrite('01.png',recomposed_image*255)
cv2.destroyAllWindows()
#lol=classifier.layers[2].output
#lol
#outputs    = [layer.output for layer in Model.layers]  
#print (layer_outs)

W_Input_Hidden_2 = classifier.layers[2].get_weights()
a = np.asarray(W_Input_Hidden_2[0])
np.savetxt("w_h_2_0.csv", a, delimiter=",")

b = np.asarray(W_Input_Hidden_2[1])
np.savetxt("w_h_2_1.csv", b, delimiter=",")

#c = np.asarray(np.reshape(np.array(layer_outs[1]),(256,12)))
#c = np.asarray(np.reshape(np.array(layer_outs[1]),(64,48)))
#np.savetxt("activation_H_1.txt", c, delimiter=",")
c=recompose_image(np.reshape(np.array(layer_outs[1]),(256,12)),64,48,4,3)
cv2.imwrite('activation_1_compressed.png',c*255)

weight_h_0=np.loadtxt("w_h_2_0.csv", delimiter=',')
weight_h_1=np.loadtxt("w_h_2_1.csv", delimiter=',')
Weight_Input_Hidden_2=[]
Weight_Input_Hidden_2.append(weight_h_0)
Weight_Input_Hidden_2.append(weight_h_1)
#layer_1=np.loadtxt("activation_H_1.txt", delimiter=',')
layer_1= cv2.imread('activation_1_compressed.png', cv2.IMREAD_GRAYSCALE)
#layer_1= np.asarray(np.reshape(np.array(layer_1),(256,12)))
layer_1=create_img_dataset('activation_1_compressed.png',64,48,4,3)
layer_1=layer_1/255
classifier_new = Sequential()
classifier_new.add(Dense(units = 16, kernel_initializer = 'uniform', activation = 'sigmoid', input_dim = 12))
classifier_new.layers[0].set_weights(Weight_Input_Hidden_2)


#y_pred = classifier_new.predict(np.reshape(np.array(layer_outs[1]),(256,12)))
y_pred = classifier_new.predict(layer_1)
recomposed_image = recompose_image(y_pred,64,64,4,4)
#recomposed_image = recompose_image(np.reshape(np.array(layer_outs[1]),(16384,12)),512,384,4,3)
#recomposed_image = recompose_image(y_pred,512,512,4,4)
cv2.imshow('Recomposed Image', recomposed_image)
cv2.waitKey(0)
cv2.imwrite('01.png',recomposed_image*255)
cv2.destroyAllWindows()
#lol=classifier.layers[2].output


 