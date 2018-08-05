#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 26 22:46:50 2017

@author: khaled
"""

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


c=recompose_image(np.reshape(np.array(layer_outs[1]),(256,12)),64,48,4,3)
cv2.imwrite('activation_1_compressed.png',c*255)
