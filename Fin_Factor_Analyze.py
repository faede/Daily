#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed May  5 14:39:26 2021

@author: zyy
"""

from sklearn.metrics import confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn import datasets
from pandas import DataFrame
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import math
from pandas import Series
from factor_analyzer import FactorAnalyzer


fname = 'fin_new.csv'
data = pd.read_csv(fname, encoding = 'utf-8')

X = data.iloc[:,4:24]
from factor_analyzer.factor_analyzer import calculate_bartlett_sphericity
chi_square_value, p_value = calculate_bartlett_sphericity(X)
print(chi_square_value, p_value)

"""
(111171.68210512122, 0.0)
"""


from factor_analyzer.factor_analyzer import calculate_kmo
kmo_all, kmo_model = calculate_kmo(X)
print(kmo_model)

"""
0.5331430399768187
"""


"""
到这里我们可以发现数据不适合做因子分析，如果适合我们可以接着按下面的处理
"""




# Create factor analysis object and perform factor analysis
fa = FactorAnalyzer(25, rotation=None)
fa.fit(X)
# Check Eigenvalues
ev, v = fa.get_eigenvalues()



# Create scree plot using matplotlib
plt.scatter(range(1,X.shape[1]+1),ev)
plt.plot(range(1,X.shape[1]+1),ev)
plt.title('Scree Plot')
plt.xlabel('Factors')
plt.ylabel('Eigenvalue')
plt.grid()
plt.show()

fa = FactorAnalyzer(5, rotation="varimax")
fa.fit(X)

print(fa.loadings_)

import seaborn as sns
df_cm = pd.DataFrame(np.abs(fa.loadings_), index=X.columns)
plt.figure(figsize = (14,14))
ax = sns.heatmap(df_cm, annot=True, cmap="BuPu")
# 设置y轴的字体的大小
ax.yaxis.set_tick_params(labelsize=15)
plt.title('Factor Analysis', fontsize='xx-large')
# Set y-axis label
plt.ylabel('Sepal Width', fontsize='xx-large')
plt.savefig('factorAnalysis.png', dpi=500)
fa.transform(X)