import os
import sys
import random

random.seed = 2

file_path = sys.argv[1]
#possible_values = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]

output = []

with open(file_path, "r") as file:
    for line in file.readlines():
        values = line.split(" ")
        new_value = round(random.uniform(0.1, 0.2), 4)
        if len(values) == 3:
            values[2] = str(new_value)
        else:
            values[1] = values[1].replace("\n", "")
            values.append(str(new_value))

        output.append(values)


with open("weights_output.txt", "w") as file:
    for line in output:
        file.write(" ".join(line)+"\n")