# -*- coding: utf-8 -*-
import csv
from sympy import *
import numpy as np
from scipy import integrate
import math
import cmath
import pandas as pd
# 读取csv至字典
csvFile = open("/Users/zyy/Documents/ssss.csv", "r")
reader = csv.reader(csvFile)

# 建立空字典
result = {}
for item in reader:
    # 忽略第一行
    if reader.line_num == 1:
        continue
    result[item[0]] = item[1]

csvFile.close()
key_list = list(np.array(list(result.keys()),dtype = 'int_') )
v_list = list(np.array(list(result.values()),dtype = 'float_'))

le = len(key_list)
i = 1
while i < le:
    if key_list[i] - 1 != key_list[i-1]:
        t = (v_list[i]-v_list[i-1])/(key_list[i]-key_list[i-1])*1+v_list[i-1]
        key_list.insert(i,key_list[i-1]+1)
        v_list.insert(i,t)
    i+=1
    le = len(key_list)


#字典中的key值即为csv中列名
dataframe = pd.DataFrame({'date':key_list,'in':v_list})

#将DataFrame存储为csv,index表示是否显示行名，default=True
dataframe.to_csv("/Users/zyy/Documents/new.csv",index=False,sep=',')
