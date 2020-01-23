import matplotlib.pyplot as plt

#create lists of x and y values
x = [1,2,3,4]
y1 = [5,7,4,6]
y2 = [8,9,11,12]

# labels will be show in legend
plt.plot(x,y1, label='First Line')
plt.plot(x,y2, label='Second Line')

plt.xlabel('x label')
plt.ylabel('y label')
plt.title('The Title\nLine 2')
plt.legend()


# everything is drawn in the background, call show to see it
plt.show()