
#---------------------------------------
#Ficha 3  

from matplotlib import pyplot as plt
#import matplotlib.pyplot as plt
import numpy as np
from PIL import Image


#---------------------------------------
#Ficha 3  - Ex 2

# Le  entre 0 e 255
image = Image.open('/content/sample_data/Rosa1024.png')
arr = np.asarray(image) #Cria um objeto numpy
plt.imshow(arr, cmap='gray', vmin=0, vmax=255)
plt.show()
print(arr.shape)
print(arr.dtype)

image_Cor = Image.open('/content/sample_data/monarch.ppm')
arr_Cor = np.asarray(image_Cor)
plt.imshow(arr_Cor)
plt.show()
print(arr_Cor.shape)
print(arr_Cor.dtype)
