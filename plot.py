import matplotlib.pyplot as plt
import sys
from numpy import loadtxt
from os import listdir

text_files = listdir(".//output")

count = len(text_files)
if (len(sys.argv) == 2):
    count = int(sys.argv[1])

for n in range(count):

    f = text_files[n]
    # Name format: "STEP V_AVG.dat"
    filename = ".".join(f.split(sep='.')[0:2]).split(sep=' ')
    data = loadtxt(f".//output//{f}")
    plt.matshow(data)
    plt.title(f"V = {filename[1]}")
    print(f"Plotting image {n+1} out of {count}")
    plt.savefig(f".//plots//{filename[0]}.png", dpi=300)
    plt.close()
