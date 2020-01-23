import matplotlib.pyplot as plt
import numpy as np 

n = 10
x = np.random.rand(n)
y = np.random.rand(n)

colors = np.random.rand(n)

plt.scatter(x,y, c = colors, marker='*')
plt.xlabel('x')
plt.ylabel('y')

plt.title('Scatter Plot Example')

# everything is drawn in the background, call show to see it
plt.show()