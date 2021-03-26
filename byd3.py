#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 25 23:28:48 2021

@author: zyy
"""


import os
import cv2
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
from sklearn.metrics import  classification_report


X = [] #定义图像名称
Y = [] #定义图像分类类标
Z = [] #定义图像像素

for i in range(1, 10):
    #遍历文件夹，读取图片
    t = []
    for f in os.listdir("photo/%s" % i):
        #获取图像名称
        t.append("photo//" +str(i) + "//" + str(f))
        #获取图像类标即为文件夹名称
        Y.append(i)
    X.append(t)
    
X = np.array(X)
print(X)

# Cac Priori probability
PrioriProb =  []
total = 0
for i in range(0,9):
    PrioriProb.append(len(X[i]))
    total += len(X[i])
for i in range(0,9):   
    PrioriProb[i] = PrioriProb[i] / total
    
print(PrioriProb)
mean_vec = []
cov_matrix = []
for i in range(0,9):
    data = []
    for pic in X[i]:
        image = cv2.imread(pic)
        img = cv2.resize(image, (256,256), interpolation = cv2.INTER_CUBIC)
        # b, g, r
        hist = cv2.calcHist([img], [2 , 1 ,0], None, [5, 5, 5], [0, 256, 0, 256, 0, 256])
        hist = 
        data.append((hist/255).flatten())
        
    data = np.array(data)
    
    mean_vec.append(np.mean(data, axis = 0))
    cov_matrix.append(np.cov(data, rowvar = False))
    
def Classify(elems):
    cla = 0
    prob = 0
    for i in range(0,9):
        
    














