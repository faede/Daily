#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 26 10:51:54 2021

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
X1 = np.matrix(X1)
X2 = np.matrix(X2)
m1 = np.mean(X1, axis = 0)
# print(X1 - m1)
m2 = np.mean(X2, axis = 0)

S1 = 0
S2 = 0
# print(X1)
for i in range(0, len(X1)):
    S1 += np.dot((X1[i] - m1).T, (X1[i] - m1))
    #print(np.dot((X1[i] - m1).T, (X1[i] - m1)))
    #print(" i :", i)
    #print(np.dot((X1[i] - m1).T, (X1[i] - m1)))
    S2 += np.dot((X2[i] - m2).T, (X2[i] - m2))
#print(X1 - m1)
#print(S1)
#print(np.dot((X1 - m1).T, (X1 - m1)))
Sw = (S1 + S2).T

m1_m2 = np.matrix(m1 - m2)
#print(m1_m2)
# print(eigvalue, eigvector)
w = -np.dot(np.linalg.inv(Sw), m1_m2.T) 
w = w / LA.norm(w,2)
print(w)
sample = np.array([9,10])
if abs(np.dot(w.T, sample.T) - np.dot(w.T, m1.T)) < abs(np.dot(w.T, sample.T) - np.dot(w.T, m2.T)):
    print('1')
else:
    print('2')
    
##  两两比较 投票