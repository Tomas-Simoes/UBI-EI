from matplotlib import pyplot as plt
import numpy as np
from PIL import Image 

image = Image.open("./class04/images/Rosa1024.png")
arr = np.asarray(image)
#plt.imshow(arr, cmap='gray', vmin=0, vmax=255)
#plt.show

print("Rosa1024 Shape: " + str(arr.shape))
print("Rosa1024 Dtype: " + str(arr.dtype))
print("Débito Binário Rosa1024.pgm: " + str(1024 + 1024 + 8) + " bits");


imageColor = Image.open('./class04/images/monarch.ppm')
arrColor = np.asarray(imageColor)
#plt.imshow(arrColor)
#plt.show()

print("Monarch: " + str(arrColor.shape))
print("Monarch:" + str(arrColor.dtype))
print("Débito Binário monarch.pgm: " + str(768 + 512 + 8) + " bits");

#? ---- Mirror Image
mirrorVertically = arr[::-1 , ::]
mirrorHorizontally = arr[:: , ::-1]
plt.imshow(mirrorVertically, cmap='grey', vmin=0, vmax=255)
#plt.show()

plt.imshow(mirrorHorizontally, cmap='grey', vmin=0, vmax=255)
#plt.show()

#? ---- Half Image
arrHalf = arr[::2]
plt.imshow(arrHalf, cmap='grey', vmin=0, vmax=255);
#plt.show()

#? ---- Ampliação 
arrRow, arrCol = arr.shape

arrDouble = np.zeros_like(arr, shape=(arrRow*2, arrCol*2))
arrDouble[::2, ::2] = arr
arrDouble[1::2, ::2] = arr 
arrDouble[::2, 1::2] = arr
arrDouble[1::2, 1::2] = arr

plt.imshow(arrDouble, cmap='grey', vmin=0, vmax=255)
#plt.show()

#? ---- Corte Central
centralRow = arrRow // 2
centralCol = arrCol // 2

arrCentral = np.zeros_like(arr, shape=(arrRow, arrCol))
arrCentral[:centralRow - 100:, ::] = arr[:centralRow - 100:, ::]
arrCentral[centralRow + 100::, ::] = arr[centralRow + 100::, ::]

arrCentral[::, centralCol - 100::] = arr[::, :centralCol - 100:]
arrCentral[::, centralCol + 100::] = arr[::, centralCol + 100:]

plt.imshow(arrCentral, cmap='grey', vmin=0, vmax=255)
plt.show()
