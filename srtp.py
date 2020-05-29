# -*- coding: utf-8 -*-
import csv
from sympy import *
import numpy as np
from scipy import integrate
import math
import cmath
# 读取csv至字典
csvFile = open("/Users/zyy/Documents/historydata.csv", "r")
reader = csv.reader(csvFile)

# 建立空字典
result = {}
for item in reader:
    # 忽略第一行
    if reader.line_num == 1:
        continue
    result[item[0]] = item[1]

csvFile.close()
v_list1 = np.array(list(result.values()),dtype = 'float_') 

v_list =[]
for i in range(0,len(v_list1)-1):
    v_list.append((v_list1[i+1]-v_list1[i]))

def f (arr,x):
    me_vl = np.mean(arr)
    le = len(arr)
    cac = complex(0,0)
    for i in range(0,le):
        cac += (arr[i]-me_vl)*complex(math.cos(-i*x),math.sin(-i*x))
    cac = 1/(le + 1)*abs(cac)*abs(cac)
    return float( cac)

x = np.linspace(-math.pi,math.pi,100)

y = x
for i in range(0,len(x)):
    y[i] = math.log(f(v_list,x[i]))

print(integrate.trapz(y, x))
