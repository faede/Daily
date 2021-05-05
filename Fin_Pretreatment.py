#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed May  5 08:39:19 2021

@author: zyy
"""

from sklearn.metrics import confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn import svm, datasets
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

un_cop_file_name = 'fin_data.csv'
# header = 1
data = pd.read_csv(un_cop_file_name, encoding='utf-8')
data2 = data.dropna()

b = 2

for index_y in range(4,23):
    col = data2.columns.values.tolist()
    
    col2 = col.copy()
    col.pop(index_y)
    
    
    col = col[4:]
    
    
    X_Train = data2[col]
    Y_Train = data2[col2[index_y]]
    
    a = 1
    from sklearn.ensemble import RandomForestRegressor as rfr
    rfr = rfr(n_estimators = 100)
    rfr = rfr.fit(X_Train, Y_Train)
    
    for i in range(0,data.shape[0]):
        if str(data.iloc[i, index_y]) == 'nan':
            temp =  pd.DataFrame( np.array(data[col2[index_y]]) ).T
            data.iloc[i, index_y] = rfr.predict(temp)
data_new = data.dropna()

#complete_fname = 'complete.csv'
#data_new.to_csv(complete_fname, index = False, header = False)