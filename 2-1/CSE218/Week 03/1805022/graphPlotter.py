import numpy as np
import matplotlib.pyplot as plt


# creating numpy array from range x = -1.99 to 10 with increament 0.05
x = np.arange(-1.99, 10, 0.05)
y = x/(1-x)* ((6/(2+x))**(0.5))-.05
y[y>100] = np.nan   # erasing asymptote
y[y<-100] = np.nan  # erasing asymptote

# Plotting the graphs
plt.ylim([-15, 15])                                                 # limiting y axis value
plt.plot([-3,10],[0,0],color='blue')                                # x-axis
plt.plot([0,0],[-15,15],color='blue')                               # y-axis
plt.plot(x, y,color = 'green',linestyle='dashed', linewidth = 3)    # main graph

# Labeling axis
plt.xlabel('x - axis - Mole Fraction ')
plt.ylabel('y - axis - F(x) ')

# Latex format for equation writer
plt.title('$Dissociation\ of\ H_2O:\ \\frac{x}{1-x} \sqrt{ \\frac{6}{2+x} }-.05$')


plt.show()
