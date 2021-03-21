# coding=utf-8

from abc import ABCMeta, abstractmethod



class Point():
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def print(self):
        print ("(", self.x, ",", self.y, ")")
   
class Elem():
     def __init__(self):
        self.value = []

class Node():
    def __init__(self):
       self.elems = []
       self.UpLevel = None
       self.NextLevel = None
        
class Tree():
    k = 3
    def __init__(self,root: Node) :
        self.root = root
        
    def insert(self, elem: Elem):
        dep = 0
        key = dep % Tree.k + 1
        
        # if it is first elem ,just insert
        hot = self.root
        if hot.NextLevel == None:
            hot.elems.append(elem)
            return 
        
        # or search right pos
        i = 0
        le = len(hot.elems)
        while hot.NextLevel != None:
            if i >= le:
                # TODO: insert to last region
                break
            elif elem[key] < hot.elems[i][key]:
                # TODO: insert
                hot = hot.NextLevel
                i = 0
                pass
            else :
                i += 1
            pass
        

        
        


        
        