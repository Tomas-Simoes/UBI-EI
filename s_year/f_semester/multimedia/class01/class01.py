import numpy as np 
import matplotlib.pyplot as plt

pi = 3.14159
time = np.arange(1/8, 1.1, 1/8)

m = 6 * np.sin(2 * pi * time)
mq = [9/2, 11/2, 9/2, -1/2, -9/2 ,-11/2, -9/2, -1/2]
halfmq = []

plt.plot(time[0:8], m[0:8], time[0:8], mq)
plt.show()

error = (m[0:8] - mq * m[0:8] - mq)
averageError = np.sum(error) / 8
codes = ['1010', '1011', '1010', '0110', '0001', '0000', '0001', '0101']

plt.plot(time[0:16], m[0:16], time[0:16], mq)
plt.show()