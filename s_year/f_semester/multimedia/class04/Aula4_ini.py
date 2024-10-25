
#---------------------------------------
#Ficha 4  

from matplotlib import pyplot as plt
import numpy as np
from PIL import Image

from skimage.color import rgb2hsv
from skimage.color import hsv2rgb

from skimage.color.colorconv import rgb2ycbcr
from skimage.color.colorconv import ycbcr2rgb


#Pergunta 1 Exemplo
R = np.zeros((256, 256,3), np.uint8)
R[:,:,0] = 255

plt.figure(figsize=(15,5))
plt.axis('off')
plt.imshow(R)


plt.show()


#Pergunta 2 Exemplo

R_deg = np.zeros((256, 256,3), np.uint8)
for i in range(255):
  R_deg[:,i,0] = i

plt.figure(figsize=(15,5))
plt.axis('off')
plt.imshow(R_deg)

plt.show()

