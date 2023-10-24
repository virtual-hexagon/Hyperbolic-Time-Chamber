import json
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import os

# open and load our json data from the cpp computations
# Notes:
# - Make sure that the vscode launch task for the python has set the key `"cwd": "${fileDirname}"`
#   to make sure that the python file when run in the terminal can find the data file
with open("data/data.json") as file:
    data = json.load(file)

# Create our figure
# Notes:
# - use the matplotlib explicit OO style API vs the pyplot style
# - subplots() default creates a single figure with a single Axes
# - set the plot format properties like title and axis labels
# - specifically set we want to view the plots on a log-log scale
# - plot our 3 derivative estimation strategies computed in c++
fig, ax = plt.subplots()  
ax.plot(data['gridSize'], data['forwardDiffError'] , label='O(1) Forward Difference')
ax.plot(data['gridSize'], data['centralDiffError'] , label='O(2) Central Difference')
ax.plot(data['gridSize'], data['centralDiff4Error'], label='O(4) Central Difference')

ax.set_title("Error vs Grid Step Size")
ax.grid(visible=True, which='both', axis='both')
ax.legend()

ax.set_xlabel("Step Size (h)")
ax.set_xscale('log')

ax.set_ylabel("Error (e)")
ax.set_yscale('log')

plt.show()