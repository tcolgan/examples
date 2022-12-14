#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

CYC = 8
DIV = 50
AMP = 10
freq = .5
damp = .1

xmax = 2 * np.pi * CYC ;
x = np.matrix( np.linspace( -xmax , xmax , DIV ) )
ones = np.matrix( np.ones( x.shape ) )
X = ones.T * x
Y = x.T * ones

R = np.sqrt( np.square( X ) + np.square( Y ) )

Z = AMP * np.multiply(  np.cos( freq * R ) , np.exp( -damp * R ) )

ax.plot_surface( X , Y , Z , rstride=1 , cstride=1 , cmap='hsv' )

plt.show()

