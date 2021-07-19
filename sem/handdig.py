#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jul 13 17:17:25 2021

@author: zyy
"""
import pandas as  pd
import numpy as np
from sklearn.model_selection import  train_test_split
from sklearn.metrics import confusion_matrix
from sklearn import metrics
import matplotlib.pyplot as plt
from sklearn.metrics import accuracy_score
import struct,os
from array import array as pyarray
from numpy import append, array, int8, uint8, zeros
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score,classification_report
import copy

def load_mnist(image_file, label_file, path = "."):


    fname_image = os.path.join(path, image_file)
    fname_label = os.path.join(path, label_file)

    flbl = open(fname_label, 'rb')
    # >：大端
    # I unsignedint
    magic_nr, size = struct.unpack(">II", flbl.read(8))
    # b signedchar
    lbl = pyarray("b", flbl.read())
    flbl.close()

    fimg = open(fname_image, 'rb')
    
    magic_nr, size, rows, cols = struct.unpack(">IIII", fimg.read(16))
    # B unsigned char
    img = pyarray("B", fimg.read())
    fimg.close()

    images = zeros((size, rows*cols), dtype = uint8)
    labels = zeros((size, 1), dtype = int8)
    for i in range(size):
        images[i] = array(img[ i *rows*cols : (i+1)*rows*cols ]).reshape((1, rows*cols))
        labels[i] = lbl[i]

    return images, labels


import matplotlib.pyplot as plt

        
if __name__=="__main__":
    train_image, train_label = load_mnist("train-images.idx3-ubyte", "train-labels.idx1-ubyte")
    test_image, test_label = load_mnist("t10k-images.idx3-ubyte", "t10k-labels.idx1-ubyte")
    train_image = [im/255.0 for im in train_image]
    test_image = [im/255.0 for im in test_image]
    
    clf = MLPClassifier(solver = 'adam', max_iter = 100, alpha = 1e-3, hidden_layer_sizes = (50,20), random_state = 1, verbose = True)
    clf.fit(train_image, train_label)
    # 模型效果获取
    r = clf.score(train_image, train_label)
    print("训练集准确率: %.4lf" % r)
    predict = clf.predict(test_image)
    print("预测集准确率: %.4lf" % accuracy_score(predict,test_label))
    
    