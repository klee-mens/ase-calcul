#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Nov  5 19:33:42 2020

@author: mens
"""

import os
import matplotlib.pyplot as plt
import numpy as np
plt.close("all")

datfiles = [f for f in os.listdir() if f[-4::] == "data"]

f1 = datfiles[0]
f2 = datfiles[1]

# fh = open(f1, "r")
# txt = fh.read()
# fh.close()
m = np.loadtxt(f1, delimiter=", ")
xmc = m[:, 0]
ymc = m[:, 1]

plt.figure()
plt.plot(xmc, ymc)
plt.xlabel("Samples in 1000", fontsize = 14)
plt.ylabel("Berechneter Gain", fontsize = 14)
plt.ylim([0, max(ymc) * 1.1])
plt.savefig("Monte_Carlo_Konvergence_Plot.png")



m = np.loadtxt(f2, delimiter=", ")
x5D = m[:, 0]
y5D = m[:, 1]

plt.figure()
plt.plot(x5D, y5D)
plt.xlabel("Anzahl der Stützstellen", fontsize = 14)
plt.ylabel("Berechneter Gain", fontsize = 14)
plt.ylim([0, max(y5D) * 1.1])
plt.savefig("Integral_5D_Konvergence_Plot.png")