from matplotlib import pyplot as plt
import numpy as np
from PIL import Image 

imgBaboon = Image.open("./class10/images/baboon.png")
arrBaboon = np.asarray(imgBaboon)

baboonFourier = np.asarray(np.fft.fftshift(np.fft.fft2(arrBaboon)))

plt.imshow(arrBaboon, cmap='grey', vmin=0, vmax=255)
plt.imshow(np.log(1 + np.abs(baboonFourier)), cmap='grey', vmin=0, vmax=255)

plt.show()