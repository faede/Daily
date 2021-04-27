#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Apr 17 15:36:50 2021

@author: zyy
"""

from sklearn.metrics import confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn import svm, datasets
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


fname = 'un_complete_processed.cleveland.data' 
with open(fname, 'r+', encoding='utf-8') as f:
    s = [i[:-1].split(',') for i in f.readlines()]

num = len(s)
for i in range(0, num):
    for j in range(0,len(s[i])):
        if s[i][j] == '?':
            s[i][j] = ''
s = np.array(s)
s = pd.DataFrame(s)

new_fname = 'new.csv'
s.to_csv(new_fname, index = False)

data = pd.read_csv(new_fname)

data2 = data.dropna()
X_Train = pd.DataFrame(data2.iloc[:,0:10]) 

for index_y in range(11,14):
    Y_Train = pd.DataFrame(data2.iloc[:,index_y]) 
    from sklearn.ensemble import RandomForestRegressor as rfr
    rfr = rfr(n_estimators = 100)
    rfr = rfr.fit(X_Train, Y_Train)
    
    for i in range(0,data.shape[0]):
        if str(data.iloc[i, index_y]) == 'nan':
            temp =  pd.DataFrame( np.array(data.iloc[i,0:10])).T
            data.iloc[i, index_y] = rfr.predict(temp)
data_new = data.dropna()

complete_fname = 'complete.csv'
data_new.to_csv(complete_fname, index = False, header = False)