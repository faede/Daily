#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 25 23:28:48 2021

@author: zyy
"""


import os
import cv2
import numpy as np
import math

X_train = [] 
Y_train = [] 

for i in range(1, 10):
    t = []
    t2 = []
    for f in os.listdir("photo/%s" % i):
        if not 't' in str(f) and not 'D' in str(f):
            t.append("photo//" +str(i) + "//" + str(f))
            t2.append(i)
    X_train.append(t)
    Y_train.append(t2)
    
X_train = np.array(X_train)

    
    
mean_vec = []
cov_matrix = []

# 3 * 3 * 3
k = 27 


# calculate hist for decsion
def CacHist(pic):
    #read image
    image = cv2.imread(pic)
    gauss = np.random.normal(0,1,image.size)
    gauss = gauss.reshape(image.shape[0],image.shape[1],image.shape[2]).astype('uint8')
    # Add the Gaussian noise to the image
    img_gauss = cv2.add(image,gauss)
    new_pic = pic[:-4] + 't.jpg'
    cv2.imwrite(new_pic, img_gauss)
    
    # read new image
    image = cv2.imread(new_pic)
    img = cv2.resize(image, (256,256), interpolation = cv2.INTER_CUBIC)
    # 0, 1, 2 is b, g, r => r, g, b [2, 1, 0]
    hist = cv2.calcHist([img], [2 , 1 ,0], None, [3, 3, 3], [0, 256, 0, 256, 0, 256])
    hist = hist + 10
    # flatten high dim matrix to one dim vector
    hist = hist.flatten()
    hist = np.log(hist)
    return hist

# calculate mean and cov 
for i in range(0,9):
    data = []
    for pic in X_train[i]:
        data.append(CacHist(pic))
        
    data = np.matrix(data)
    mean_vec.append(np.mean(data, axis = 0))
    cov_matrix.append(np.cov(data, rowvar = False))
    
    
# Bayesian decision
def Classify(sample):
    cla = np.zeros(1,9)
    for i in range(0,8):
        for j in range(i+1, 9):
            m1 = mean_vec[i]

            m2 = mean_vec[j]

            S1 = 0
            S2 = 0
            for i in range(0, len(X1)):
                S1 += np.dot((X1[i] - m1).T, (X1[i] - m1))
                S2 += np.dot((X2[i] - m2).T, (X2[i] - m2))
            Sw = (S1 + S2).T

            m1_m2 = np.matrix(m1 - m2)
            w = -np.dot(np.linalg.inv(Sw), m1_m2.T) 
            w = w / LA.norm(w,2)
            print(w)
            sample = np.array(sample)
            if abs(np.dot(w.T, sample.T) - np.dot(w.T, m1.T)) < abs(np.dot(w.T, sample.T) - np.dot(w.T, m2.T)):
                cla[i] = cla[i] + 1
            else:
                cla[j] = cla[j] + 1
    return np.argmax(cla) 


X_test = [] 
Y_test = [] 

total_test = 0
for i in range(1, 10):
    t = []
    t2 = []
    for f in os.listdir("photo2/%s" % i):
        if not 't' in str(f) and not 'D' in str(f):
            total_test = total_test + 1
            t.append("photo2//" +str(i) + "//" + str(f))
            t2.append(i)
    X_test.append(t)
    Y_test.append(t2)
    
X_test = np.array(X_test)

classify_right = 0
confusion_matrix = np.zeros((9,9))
for j in range(0,9):
    for i in X_test[j]:
        c = Classify(CacHist(i))    
        confusion_matrix[j][c] = confusion_matrix[j][c] + 1
        if c == j:
            classify_right = classify_right + 1
            
            
print('混淆矩阵:')
print(confusion_matrix)
print('正确率:','%.2f'% (classify_right / total_test * 100), '%')