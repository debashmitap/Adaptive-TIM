import os
import sys

input_path = sys.argv[1]
output_path = sys.argv[2]


d = {}
output = []
nodes = 0
edges = 0
with open(input_path, "r") as snap_file:
    for line in snap_file.readlines():
        a, b, c = line.split(" ")
        o = ""
        if a not in d.keys():
            d[a] = str(nodes)
            nodes += 1
        o += d[a]
        o += " "
        if b not in d.keys():
            d[b] = str(nodes)
            nodes += 1
        o += d[b]
        o += " "+c
        output.append(o)
        edges += 1

if not os.path.exists(output_path):
    os.makedirs(output_path)

graph_path = os.path.join(output_path, "graph_ic.inf")
with open(graph_path, "w") as graph_file:
    graph_file.writelines(output)

attribute_path = os.path.join(output_path, "attribute.txt")
with open(attribute_path, "w") as attribute_file:
    attribute_file.write("n="+str(nodes)+"\n")
    attribute_file.write("m="+str(edges)+"\n")

n_path = os.path.join(output_path, "n.txt")
with open(n_path, "w") as n_file:
    n_file.write(str(nodes)+"\n")
