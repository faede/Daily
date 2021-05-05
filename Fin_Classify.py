#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed May  5 11:59:37 2021

@author: zyy
"""

from sklearn.metrics import confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn import datasets
from pandas import DataFrame
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import math


fname = 'fin_new.csv'
data = pd.read_csv(fname, encoding = 'utf-8')
X = data.iloc[:,4:23]
Y = data.iloc[:,23]

X_train,X_test,Y_train, Y_test = train_test_split(X, Y, test_size = 0.3, random_state = 0)
sc = StandardScaler()
sc.fit(X)

standard_train = sc.transform(X_train)
standard_test = sc.transform(X_test)


SVMClassifier = SVC(kernel = "linear", decision_function_shape = 'ovo',gamma = 'auto')
SVMClassifier.fit(standard_train, Y_train)
result = SVMClassifier.predict(standard_test)
print("线性分类器：")
#print(list(Y_test))
#print(list(result))
print(SVMClassifier.score(standard_test,Y_test))


SVMClassifier = SVC(kernel = "poly", degree = 3, decision_function_shape = 'ovo',gamma = 'auto')
SVMClassifier.fit(standard_train, Y_train)
result = SVMClassifier.predict(standard_test)
print("多项式核函数非线性分类器：")
#print(list(Y_test))
#print(list(result))
print(SVMClassifier.score(standard_test,Y_test))


SVMClassifier = SVC(kernel = "rbf", decision_function_shape = 'ovo', gamma = 'auto')
SVMClassifier.fit(standard_train, Y_train)
result = SVMClassifier.predict(standard_test)
print("高斯核函数非线性分类器：")
#print(list(Y_test))
#print(list(result))
print(SVMClassifier.score(standard_test, Y_test))





