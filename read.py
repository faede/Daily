#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Apr 17 15:36:50 2021

@author: zyy
"""
#Importing the necessary packages and libaries
from sklearn.metrics import confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn import svm, datasets
import matplotlib.pyplot as plt
import numpy as np


fname = 'un_complete_processed.cleveland.data' 
with open(fname, 'r+', encoding='utf-8') as f:
    s = [i[:-1].split(',') for i in f.readlines()]
t = 0
X = []
y = []
for i in s:
    #t = t + 1
    #if t > 1:
    #    break
    X.append(i[0:13])
    y.append(i[13])
X = np.array(X)
y = np.array(y)

X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=0.8, random_state = 0)

