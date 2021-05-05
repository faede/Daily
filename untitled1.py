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
import math

un_cop_file_name = 'fin_data.csv'
# header = 1
data = pd.read_csv(un_cop_file_name, encoding='utf-8')
data2 = data.dropna()
col = data2.columns.values.tolist()
    


col = col[4:]

data_max = data2[col].max().values.tolist()
data_min = data2[col].min().values.tolist()

# data3 = data2[col].apply(np.log1p)
def max_min_log_deal(x, i):
    y = (x - data_min[i]) / (data_max[i] - data_min[i])
    if y < 0:
        print('error this i:',i , 'y :',y)
    y = math.log2(y + 1)
    return y

def max_min_deal(x, i):
    y = (x - data_min[i]) / (data_max[i] - data_min[i])
    return y

for i in range(0,19):
    ca_name = col[i]
    data2[ca_name] = data2[ca_name].apply(max_min_log_deal, args = (i, ))

data3 = data2[col]
    
from sklearn.cluster import SpectralClustering
model1 = SpectralClustering(n_clusters = 3)
#yhat1 = model1.fit_predict(data3)

  
    
from sklearn.cluster import DBSCAN
model2 = DBSCAN(eps=0.30, min_samples = 5)
#yhat2 = model2.fit_predict(data3)
    
  
# may most
from sklearn.mixture import GaussianMixture
model3 = GaussianMixture(n_components=3)
model3.fit(data3)
yhat3 = model3.predict(data3)

from sklearn.cluster import MiniBatchKMeans
model4 = MiniBatchKMeans(n_clusters=3)
model4.fit(data3)
#yhat4 = model4.predict(data3)


res = {}
# {name : sum , num}
for i in range(9682):
    find_name = data2['证券简称'].values.tolist()[i]
    if find_name in res:
        res[find_name][0] = res[find_name][0] + yhat3[i]
        res[find_name][1] += 1
    else:
        res[find_name] = [yhat3[i], 1]
res_e = {}

for key in res.keys():
    res_e[key] = int(round(res[key][0] / res[key][1])) + 1
    

data2.insert(data.shape[1], 'classify', 0)
for i in range(9682):
    data2.iat[i, 23] = res_e[data2.iat[i, 2]]
    
new_fname = 'fin_new.csv'
# data2.to_csv(new_fname, index = False, header = False)
data2.to_csv(new_fname)