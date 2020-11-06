#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Nov  6 12:51:11 2020

@author: mens
"""

import os
import matplotlib.pyplot as plt
import numpy as np
plt.close("all")


datfiles = [f for f in os.listdir() if f[-4::] == "data"]

f1 = 'konvergence_moncar.data'
f2 = 'konvergence_5D.data'

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


# just for me
plt.figure()
x2 = xmc / 10
plt.plot(x5D, y5D)
plt.plot(x2, ymc)

# geometrie plot
file = 'geometric_behaviour.data'
Matrx = np.loadtxt(file, delimiter=", ", skiprows=1)
x = Matrx[:,0]
y = Matrx[:,1]
start = 20
plt.figure()
plt.plot(x[start::],y[start::])
plt.xlabel(r"Verhältnis Länge zu Breite des Kristalls $\gamma$", fontsize=14)
plt.ylabel("Berechneter Gain", fontsize=14)
plt.savefig("Geometrisches_Verhalten.png")
