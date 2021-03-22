#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Mar 22 08:01:24 2021

@author: zyy
"""


import numpy as np
from sklearn.neural_network import MLPClassifier  
import matplotlib.pyplot as plt
X = np.array([[0., 0.], [1., 1.], [-1.,1.], [0.,2.], [-2.,0.], [2.,0.]])  
y = np.array([0,0,0,1,1,1])  

clf = MLPClassifier(solver='lbfgs', alpha=1e-5,  
                hidden_layer_sizes=(5, 2), random_state=1)  

clf.fit(X, y)
def plot_decision_boundary(pred_func):  

    # 设定最大最小值，附加一点点边缘填充  
    x_min, x_max = X[:, 0].min() - .5, X[:, 0].max() + .5  
    y_min, y_max = X[:, 1].min() - .5, X[:, 1].max() + .5  
    h = 0.01  

    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))  

    # 用预测函数预测一下  
    Z = pred_func(np.c_[xx.ravel(), yy.ravel()])  
    Z = Z.reshape(xx.shape)  

    # 然后画出图  
    plt.contourf(xx, yy, Z, cmap=plt.cm.Spectral)  
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.Spectral)   

plot_decision_boundary(lambda x: clf.predict(x))
plt.title("MLP Classification")
plt.show()