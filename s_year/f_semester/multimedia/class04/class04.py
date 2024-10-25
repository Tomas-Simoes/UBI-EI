from matplotlib import pyplot as plt
import numpy as np
from PIL import Image

image = Image.open("./class04/images/pepper.png")
arrColor = np.asarray(image)

indexedImg = image.convert('P', dither=None, palette="Palette.ADAPTIVE", colors = 256);
arr = np.asarray(indexedImg)

plt.figure(figsize=(25,5))

"""
? Create PLOT with 1 row and 6 columns. Editing the index 1.
? Using the indexed image arr in order to change the collor palette
"""

plt.subplot(261)
plt.axis('off')
plt.imshow(arr, cmap='viridis', vmin=0, vmax=255)
plt.title("Viridis")

plt.subplot(262)
plt.axis('off')
plt.imshow(arr, cmap='magma', vmin=0, vmax=255)
plt.title("Magma")

plt.subplot(263)
plt.axis('off')
plt.imshow(arr, cmap='cividis', vmin=0, vmax=255)
plt.title("Cividis")

plt.subplot(264)
plt.axis('off')
plt.imshow(arr, cmap='gray', vmin=0, vmax=255)
plt.title("Gray")

plt.subplot(265)
plt.axis('off')
plt.imshow(arr, cmap='inferno', vmin=0, vmax=255)
plt.title("Inferno")

plt.subplot(266)
plt.axis('off')
plt.imshow(arr, cmap='plasma', vmin=0, vmax=255)
plt.title("Plasma")

"""
? GIFs are already indexed images so you don't need to index it
"""
imageGif = Image.open("./class04/images/200_s.gif")
arrGif = np.asarray(imageGif)

plt.subplot(267)
plt.axis('off')
plt.imshow(arrGif, cmap="magma", vmin=0, vmax=255)
plt.title("Magma GIF")

plt.tight_layout()  
plt.show()