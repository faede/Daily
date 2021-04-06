#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Mar 31 15:37:37 2021

@author: zyy
"""

import os
import cv2
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
from sklearn.metrics import  classification_report
from numpy.linalg import eig
from numpy import linalg as LA



X1 = [[4,1],[2,4],[2,3],[3,6]]
X2 = [[9,10],[6,8],[9,5],[10,8]]
cont = []
#print(X2)
Y = [1, 1, 1, 1, -1, -1, -1, -1]
# for l in X2:
#     t = []
#     for j in l:
#         #print('j:',j)
#         t.append(-j)
#     cont.append(t)
# cont = cont + X1
cont = X1.copy()
cont = cont + X2
le = len(cont)
vec = np.array( [0, 0])
b = 0
cont = np.array(cont)


index = 0
need_next = True
count = 0
times = 0

alpha = 1
while need_next:
    #need_next = False
    if (np.dot(cont[index], vec) + b ) * Y[index] <= 0:
        vec = vec + cont[index] * Y[index] * alpha
        b = b + Y[index] * alpha
        #need_next  = True
        times = times + 1
        count = 0
    else:
        count = count + 1
    index = (index + 1) % le
    if count <= le - 1:
        need_next = True
    else:
       need_next = False 
    
    
vec = - vec / LA.norm(vec,2)
print('tiems: ', times)
print(vec,b)
    