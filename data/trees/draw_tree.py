# -*- coding: utf-8 -*-
import pydot
import sys 

def print_graph(file):
    graph = pydot.Dot(graph_type='graph')
    try:
        f = open(file, "r")
        
        for line in f.readlines()[1:]:
            u,v =  line.split("=")
            edge = pydot.Edge(v[:len(v)-1], u[1:])
            graph.add_edge(edge)

        graph.write_png('{}.png'.format(file))
        print "{} was successful".format(file)

    except:
        print "{} does not exist".format(file)

cases = ["ICRA", "CQAA", "CQARA", "RPL"]

for i in range(43,44,1):
    for x in range(4):
        file_name = "tree_{}_{}.dat".format(i,cases[x])
        print_graph(file_name)
