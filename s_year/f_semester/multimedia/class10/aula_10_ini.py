
# -*- coding: utf-8 -*-
"""Aula_10_ini.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1e_JacWY05pKu5UylAZtGy4jy4EG-Szpj
"""

import matplotlib.pyplot as plt 
import numpy as np
from PIL import Image

"""# 1. Leia a imagem **baboon**, converta-a para níveis de cinza e reduza-a para metade. 
# 2. Calcule a *fft* da imagem **baboon** (*np.fft.fftshift(np.fft.fft2(baboon)*). O *fftshift* serve para centrar as baixas frequências.
#3. Represente a imagem **baboon** no espaço e também em função das frequências.
"""
imgBaboon = Image.open(r'C:\Users\tomas\Desktop\Folders\Developer\UBI-EI\s_year\f_semester\multimedia\class10\images\baboon.png').convert('L')
arrBaboon = np.asarray(imgBaboon)
baboon = arrBaboon[::2,::2]*1.0

Baboon=np.fft.fftshift(np.fft.fft2(baboon))

"""
plt.rcParams['figure.figsize'] = (6, 3)
plt.subplot(1,2,1)
plt.imshow(baboon, cmap='gray')
plt.axis('off')
plt.subplot(1,2,2)
plt.imshow(np.log(1+np.abs(Baboon)), cmap='gray')
plt.axis('off')
plt.show()
print(np.shape(baboon), np.min(baboon), np.max(baboon), baboon.dtype, Baboon.dtype)
"""

"""# Máscaras"""

[L,C] = np.shape(baboon)
L2 = int(L/2)
C2 = int(C/2)
L,C, L2, C2

x = np.linspace(1-C2, C2, C)

y = np.linspace(1-L2, L2, L)

xv, yv = np.meshgrid(x, y)

z=np.sqrt(xv*xv + yv*yv)

c1=z>15
c2=z>50
c3=z<50
c4=z<15

""" 
plt.figure(figsize=(15,40))
#plt.imshow(np.hstack((c1,c2,c3,c4)), cmap='gray', vmin=0, vmax=1)

plt.subplot(1,4,1)
plt.imshow(c1, cmap = 'gray')
plt.subplot(1,4,2)
plt.imshow(c2, cmap = 'gray')
plt.subplot(1,4,3)
plt.imshow(c3, cmap = 'gray')
plt.subplot(1,4,4)
plt.imshow(c1, cmap = 'gray')
#plt.axis('off')
#plt.show()
 """
"""# 4. Use as máscaras c1 e c2 definidas no ficheiro Aula_10.py para remover as frequências mais baixas. Analise as imagens resultantes, após proceder à inversa da transformada de Fourier (*np.fft.ifft2(hp)*)."""

#High Pass Filtering in Fourier Domain 
c1Baboon = Baboon * c1
c2Baboon = Baboon * c2
hpi = np.fft.ifft2(c1Baboon)

plt.figure(figsize=(15,40))
plt.subplot(1,4,1)
plt.imshow(np.log(1+np.abs(Baboon)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,2)
plt.imshow(np.log(1+np.abs(c1Baboon)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,3)
plt.imshow(np.log(1+np.abs(c2Baboon)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,4);
plt.imshow(np.abs(hpi), cmap = 'gray')
plt.axis('off')

plt.show()
 
""" 
# 5. Use as m´ascaras c3ec4 definidas no ficheiro Aula 10.py para remover as frequências 
mais altas. Analise as imagens resultantes, após proceder à inversa da transformada de Fourie
"""
c3Baboon = Baboon * c3 
c4Baboon = Baboon * c4

plt.figure(figsize=(15,40))
plt.subplot(1,4,1)
plt.imshow(np.log(1+np.abs(Baboon)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,2)
plt.imshow(np.log(1+np.abs(c3Baboon)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,3)
plt.imshow(np.log(1+np.abs(c4Baboon)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,4)
plt.imshow(np.abs(np.fft.ifft2(c3Baboon)), cmap = 'gray')
plt.axis('off')

plt.show()

"""# 6. Faça as ultimas alineas para a imagem saturn
"""
imgSaturn = Image.open(r"C:\Users\tomas\Desktop\Folders\Developer\UBI-EI\s_year\f_semester\multimedia\class10\images\saturn.png")
arrSaturn = np.asarray(imgSaturn)
saturn = arrSaturn[::2, ::2] * 1.0

Saturn = np.fft.fftshift(np.fft.fft2(saturn))

[L,C] = np.shape(saturn)
L2 = int(L/2)
C2 = int(C/2)
L,C, L2, C2

x = np.linspace(1-C2, C2, C)

y = np.linspace(1-L2, L2, L)

xv, yv = np.meshgrid(x, y)

z=np.sqrt(xv*xv + yv*yv)

c1=z>15
c2=z>50
c3=z<50
c4=z<15

c1Saturn = Saturn * c1
c2Saturn = Saturn * c2

plt.figure(figsize=(15,40))
plt.subplot(1,4,1)
plt.imshow(np.log(1+np.abs(Saturn)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,2)
plt.imshow(np.log(1+np.abs(c1Saturn)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,3)
plt.imshow(np.log(1+np.abs(c2Saturn)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,4);
plt.imshow(np.abs(np.fft.ifft2(c1Saturn)), cmap = 'gray')
plt.axis('off')

plt.show()
 
c3Saturn = Saturn * c3 
c4Saturn = Saturn * c4

plt.figure(figsize=(15,40))
plt.subplot(1,4,1)
plt.imshow(np.log(1+np.abs(Saturn)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,2)
plt.imshow(np.log(1+np.abs(c3Saturn)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,3)
plt.imshow(np.log(1+np.abs(c4Saturn)), cmap = 'gray')
plt.axis('off')

plt.subplot(1,4,4)
plt.imshow(np.abs(np.fft.ifft2(c3Saturn)), cmap = 'gray')
plt.axis('off')

plt.show()



"""# DCT 2D Global

# 8. Nas perguntas seguintes use as funções dct2 e idct2 definidas no ficheiro Aula_10.py para efetuar a transformada DCT e a respetiva inversa.

## Definição da DCT 2D
"""
 
from scipy.fftpack import dct
from scipy.fftpack import idct
import numpy as np

#2D Discrete Cosine Transform
def dct2(f):
    return dct(dct(f, axis=0, norm='ortho' ),axis=1, norm='ortho')

#2D Inverse Discrete Cosine Transform
def idct2(f):
    return idct(idct(f, axis=0 , norm='ortho'), axis=1 , norm='ortho')

"""# 9. Calcule a transformada DCT das imagens **baboon** e **saturn**. Proceda à representação das imagens no tempo e na frequência. Compare a distribuição das frequências entre as duas imagens."""

np.shape(imgSaturn), np.min(imgSaturn), np.max(imgSaturn)

saturn_dct = dct2(imgSaturn)

plt.figure(figsize=(15,15))
plt.imshow(np.hstack((imgSaturn,saturn_dct*10)), cmap='gray', vmin=0, vmax=255)
plt.show()
 
"""# DCT 2D por Blocos"""

""" # dct2 por blocos de 8x8
def dct2_blocos(f):   
  patch_size = 8  #8x8 patch
  f_blocos = np.zeros_like(f)
  for i in range(0,f.shape[0],patch_size):
      for j in range(0,f.shape[1],patch_size):
          f_blocos[i:(i+patch_size),j:(j+patch_size)] = dct2(f[i:(i+patch_size),j:(j+patch_size)])
  return f_blocos

def idct2_blocos(f):   
  patch_size = 8  # blocos de 8x8
  f_comp = np.zeros_like(f)
  for i in range(0,f.shape[0],patch_size):
      for j in range(0,f.shape[1],patch_size):
          f_comp[i:(i+patch_size),j:(j+patch_size)] = idct2(f[i:(i+patch_size),j:(j+patch_size)])
  return f_comp
 """
"""# Se quiser calcular taxas de compressão e PSNR
# Exemplo para o saturn 
"""
""" 
#Compute size of compressed image and compression ratio
frac_nonzero = np.sum(saturn_thresh != 0.0)/saturn.size
print("Keeping %.2f%% of DCT coefficients"%(100*frac_nonzero))
print('Compression ratio: %.1f:1'%(1/frac_nonzero))

#Compute Peak Signal to Noise Ratio (PSNR)
MSE = np.sum((saturn-saturn_comp)**2)/saturn.size
PSNR = 10*np.log10(np.max(saturn)**2/MSE)
print('PSNR: %.2f dB'%PSNR)
 """
"""# 14. Crie uma função quantiza para efetuar a quantização usando a tabela de quantização do jpeg. Pode usar uma variável fator que  multiplica pela tabela de quantização de forma a alterar estes valores.

# 15. Crie uma função dequantiza que efetua o inverso da anterior.
"""
""" 
#Quantization table jpeg
Q = np.array([ [ 16, 11, 10, 16, 24,  40,  51, 61],
      [12, 12, 14, 19, 26,  58,  60, 55],
      [14, 13, 16, 24, 40,  57,  69, 56],
      [14, 17, 22, 29, 51,  87,  80, 62],
      [18, 22, 37, 56, 68, 109, 103, 77],
      [24, 35, 55, 64, 81, 104, 113, 92],
      [49, 64, 78, 87, 103, 121, 120, 101],
      [72, 92, 95, 98, 112, 100, 103, 99]] )

#Quantization 
def quantization(f, fator):   
    return np.round(f/(fator*Q))

#Inverse Quantization
def iquantization(f, fator):
    return f*(fator*Q) """