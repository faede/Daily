#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Jul 16 15:13:37 2021

@author: zyy
"""

import csv 
from igraph import Graph as  IGraph

# read data and skip first line items
# save data in edges

def read_data(filename): 
    edges = [] 
    firstline = True 
    with open(filename,'r',encoding = 'utf-8') as f: 
        for row in csv.reader(f.read().splitlines()): 
            if firstline == True: 
                firstline = False 
                continue 
            u, v, weight = [i for i in row] 
            edges.append((u,v,int(weight))) 
    return edges 


# Using package IGraph TupleList function, generate graph depends on tuple edges
# undirected 
def get_igraph(edges): 
    g = IGraph.TupleList(edges = edges, directed = False, vertex_name_attr = "name", \
                         edge_attrs = None, weights = True) 
    return g 


# Get Game of Thrones characters name and relation weight
# output 10 items
def get_graphData(graph): 
    names = graph.vs["name"] 
    weights = graph.es["weight"] 
    print('Character name :', names[:10]) 
    print('Relation weight :', weights[:10]) 
    return names, weights 


# Degree Centrality
def Degree_Centrality(g): 
    p = list(zip(g.vs['name'],g.vs.degree())) 
    p_sort = sorted(p,key = lambda p:p[1], reverse = True) 
    return p_sort 


# Weighted Degree Centrality
def Weighted_Degree_Centrality(g,edges): 
    WDC = [] 
    for p in g.vs: 
        neighbors = [x['name'] for x in p.neighbors()] 
        weightedDegree = sum([w for a, b, w in edges for c in neighbors \
                          if (a == p['name']) and  b == c or (b == p['name'] and a == c)])
        WDC.append([p['name'], weightedDegree]) 
    WDC_sort = sorted(WDC, key = lambda p:p[1], reverse = True) 
    return WDC_sort 



# Neighbor Average Degree
def Neighbor_Average_Degree(g): 
    p = list(zip(g.vs['name'], g.knn()[0])) 
    p_sort = sorted(p, key = lambda p:p[1], reverse = True) 
    return p_sort 


# Betweenness Centrality
def Betweenness_Centrality(g): 
    p = list(zip(g.vs['name'], g.betweenness())) 
    p_sort = sorted(p, key = lambda p:p[1], reverse = True) 
    return p_sort 


# Closeness Centrality
def Closeness_centrality(g): 
    p = list(zip(g.vs['name'], g.closeness())) 
    p_sort = sorted(p, key = lambda p:p[1], reverse = True) 
    return p_sort 


# PageRank
def PageRank(g): 
    p = list(zip(g.vs['name'], g.pagerank())) 
    p_sort = sorted(p, key = lambda p:p[1], reverse = True) 
    return p_sort


# Community Detection
def Community_Detection(g): 
    clusters = IGraph.community_walktrap(g, weights = "weight").as_clustering() 
    n = len(clusters.sizes()) 
    for i in range(n): 
        print('Community', i, ":", [g.vs['name'][j] for j in clusters[i]]) 
    return clusters



if __name__ == '__main__': 
    # read data
    edges = read_data('stormofswords.csv') 
    # generate graph
    g = get_igraph(edges)
    
    
    # characters name and relation weight
    names, weights = get_graphData(g) 
    
    
    # Analyze
    print('-----------------------------------------------------------------------------------------------') 
    # Number Of Characters
    print('Number of Characters: ', g.vcount()) 
    # The Role on The Diameter
    print('The Network Diameter: ', g.diameter()) 
    print('The Role on The Diameter: ', [names[x] for x in g.get_diameter()]) 
 
    
 
    print('-----------------------------------------------------------------------------------------------') 
    # Get Shortest Path Using Function of IGraph , get_shortest_paths and  get_all_shortest_paths 
    print('The Length of Shortest Path  From Catelyn to Drogo :', \
                              g.get_shortest_paths('Catelyn','Drogo')[0])
  
    print('The Shortest Path From Catelyn to Drogo :', [names[x]   \
                               for x in   g.get_shortest_paths('Catelyn', 'Drogo')[0]]) 
    print('\r All Shortest Path From Catelyn to Drogo :') 
    paths = g.get_all_shortest_paths('Catelyn', 'Drogo') 
    for p in paths: 
        print([names[x] for x in p]) 
 
    print('-----------------------------------------------------------------------------------------------') 
    
    
    # Degree Centrality
    print('Degree Centrality: ', Degree_Centrality(g)[:10]) 
    print('Weighted Degree Centrality: ', Weighted_Degree_Centrality(g, edges)[:10]) 
    print('Neighbor Average Degree: ', Neighbor_Average_Degree(g)[:10]) 
    print('Betweenness Centrality: ', Betweenness_Centrality(g)[:10]) 
    print('Closeness centrality: ', Closeness_centrality(g)[:10]) 
    print('PageRank Alg: ', PageRank(g)[:10]) 
 
    print('-----------------------------------------------------------------------------------------------') 
    print('Community Detection: ', Community_Detection(g))