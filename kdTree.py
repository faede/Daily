#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar 21 19:27:20 2021

@author: zyy
"""


import copy
import math
# constant, great than  MAX_DISTANCE will be ignored
MAX_DISTANCE = 1e10

class Node():
    def __init__(self):
        # self.region = None
        self.val = None
        self.fa = None
        self.left = None
        self.right = None
        self.key = 0
        

def dis(l1: list, l2: list):
    sqsum = 0
    for i in range (0, len(l1)):
        sqsum += (l1[i] - l2[i])*(l1[i] - l2[i])
    return math.sqrt(sqsum)


def GetMedian(key: int, col: list) -> int:
    l = []
    for i in col:
        l.append(i[key])
    k = copy.deepcopy(l)
    k.sort()
    le = len(k)
    if le % 2 == 0:
        mid = (k[le//2] + k[le//2-1])/2
    else:
        mid = k[le//2]
        
    rem =  0
    for i in range(1,le):
        if abs(l[i] - mid)  < abs(l[rem] - mid):
            rem = i
        elif (abs(l[i] - mid)  ==  abs(l[rem] - mid) ) and (l[i] > l[rem]):
            rem = i
    return rem  


class Tree():
    k = 3
    def __init__(self) :
        self.root = Node()
    def BuildTree (self,elems: list):
        self.root = self.__Build(self.root ,elems, 0)
        

        
            
    def __Build(self, root: Node,elems: list, dep: int):
        if len(elems) == 0:
            return None
        key: int = dep % Tree.k
        index = GetMedian(key, elems)
        root = Node()
        root.val = elems[index]
        root.key = key
        
        ll = []
        rr = []
        le = len(elems)
        for i in range(0,le) :
            if i != index and elems[i][key] <= elems[index][key] :
                ll.append(elems[i])
            elif i != index and elems[i][key] > elems[index][key] :
                rr.append(elems[i])
        
        root.left = self.__Build(root.left, ll, dep + 1)
        root.right = self.__Build(root.right, rr, dep + 1)
        if root.left != None:
            root.left.fa = root
        if root.right != None:
            root.right.fa = root
        return root

    def __SearchAux(self,top: Node, e: list, m, p):
        mindis = m
        minpos = p
        if dis(top.val, e) < mindis:
                mindis = dis(top.val, e)
                minpos = top.val
        hot = top
        while hot != None:
            fahot = hot
            if (hot.val[hot.key] >= e[hot.key]):
                hot = hot.left
            else:
                hot = hot.right
        hot = fahot
        if dis(hot.val, e) < mindis:
            mindis = dis(hot.val, e)
            minpos = hot.val
        while(hot != top):
            if dis(hot.val, e) < mindis:
                mindis = dis(hot.val, e)
                minpos = hot.val
            if hot.fa.val[hot.fa.key] <= e[hot.fa.key] + mindis \
                        and  hot.fa.val[hot.fa.key] >= e[hot.fa.key] - mindis:
                if hot.fa.left == hot:
                    if hot.fa.right != None and dis(hot.fa.right.val, e) < mindis:
                        mindis = dis(hot.fa.right.val, e)
                        minpos = hot.fa.right.val
                        # recursion
                        self.__SearchAux(hot.fa.right, e, mindis, minpos)
                else:
                    if dis(hot.fa.left.val, e) < mindis:
                        mindis = dis(hot.fa.left.val, e)
                        minpos = hot.fa.left.val
                        # recursion
                        self.__SearchAux(hot.fa.left, e, mindis, minpos)
            hot = hot.fa
        return minpos
    
    
    def Search(self, e :list):
        minpos = self.__SearchAux(self.root, e, MAX_DISTANCE, None)
        mindis = dis(minpos,e)
        if dis(self.root.val, e) < mindis:
                mindis = dis(self.root.val, e)
                minpos = self.root.val
        if self.root.val[0] <= e[0] + mindis \
                         and  self.root.val[0] >=  e[0] - mindis:
                if self.root.val[0] >= e[0]:
                     if self.root.right != None:
                         minpos = self.__SearchAux(self.root.right, e, mindis, minpos)
                         mindis = dis(minpos,e)
                else:
                     minpos = self.__SearchAux(self.root.left, e, mindis, minpos)
                     mindis = dis(minpos,e)
        return minpos


      
if __name__ == "__main__":
    l = [[5,2,3], [2, 3,2], [1, 1, 7], [4 ,2 ,2], [2 , 1, 5], [7, 2 ,1]]
    t = Tree()
    t.BuildTree(l)
    print(t.root.val)
    print(t.root.left.val)
    print(t.root.left.left.val)
    print(t.root.right.val)
    print(t.root.left.fa.val)
   
    test = [[1,1,1],[1,1,10],[2,4,10]]
    for i in test:
        print("result:")
        print(t.Search(i))
        print("distance:")
        print(dis(t.Search(i),i))