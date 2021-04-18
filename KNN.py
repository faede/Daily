#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 18 10:14:47 2021

@author: zyy
"""



import os
import cv2
import numpy as np
import math
from numpy import linalg as LA
from scipy import stats

X_train = [] 
Y_train = [] 
MAX_DISTANES = 1e10
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
Y_train = np.array(Y_train)
    
    
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


X_train = X_train.flatten()
Y_train = Y_train.flatten()

X_train_data = []
for i in X_train:
    train_pic = CacHist(i)
    X_train_data.append(train_pic)
    
k_near = 3
near = np.ones(k_near) * MAX_DISTANES
clas = np.zeros(k_near)

def cac_dis(i: list, j: list) -> float:
    sq_sum = 0
    l = len(i)
    for m in range(0,l):
        sq_sum += (i[m] - j[m]) * (i[m] - j[m])
    return math.sqrt(sq_sum)

# KNN decision
def Classify(sample):
    near = np.ones(k_near) * MAX_DISTANES
    clas = np.zeros(k_near)
    l_cla = len(X_train_data)
    for i in range(0, l_cla):
        dis = cac_dis(X_train_data[i], sample)
        for j in range (0,k_near):
            if dis < near[j]:
                near[j] = dis
                clas[j] = Y_train[i] - 1
                break
    return stats.mode(clas)[0][0] 


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
        c = int(Classify(CacHist(i)))
        confusion_matrix[j][c] = confusion_matrix[j][c] + 1
        if c == j:
            classify_right = classify_right + 1
            
            
print('混淆矩阵:')
print(confusion_matrix)
print('正确率:','%.2f'% (classify_right / total_test * 100), '%')