#import wave
import matplotlib.pyplot as plt
import numpy as np
import os

from scipy.io import wavfile

# https://ipython.org/ipython-doc/stable/api/generated/IPython.display.html
# Para testar o Audio
from IPython.display import Audio, display
framerate = 44100
t = np.linspace(0,5,framerate*5)
data = np.sin(2*np.pi*220*t) + np.sin(2*np.pi*224*t)
Audio(data,rate=framerate)


def getDuration(sample_audio, sample_freq):
  n_sample_audio = sample_audio.size
  duration_audio = n_sample_audio / sample_freq
  return duration_audio

def drawAudio(audio, audioFreq):
  time = np.linspace(0, len(audio) / audioFreq, num=len(audio))
  plt.plot(time, audio)

  plt.title('Forma de Onda do Áudio')
  plt.xlabel('Tempo (s)')
  plt.ylabel('Amplitude')
  plt.show()


"""
# 1 - Ler os ficheiros de áudio 'bass.wav', 'guitar.wav', 'drums.wav'.

"""
sample_freq_bass, bass = wavfile.read("./music/drums.wav")
sample_freq_guitar, guitar = wavfile.read('./music/guitar.wav')
sample_freq_drums, drums = wavfile.read('./music/drums.wav')

"""
# 2 - Verificar a frequência de amostragem de cada um dos áudio.

"""
print("Frequência de amostragem Bass:", sample_freq_bass, "Hz")
print("Frequência de amostragem Guitar:", sample_freq_guitar, "Hz")
print("Frequência de amostragem Drums:", sample_freq_drums, "Hz")


"""
# 3 - Verificar a duração em segundos de cada áudio.
 
"""

L, = bass.shape
print(L)
print(bass.size, bass.shape)

n_samples_bass = bass.size
duration_bass = n_samples_bass/sample_freq_bass
print('\nnumero total de amostras bass:', n_samples_bass)
print('duração do audio bass (segundos):', duration_bass)

n_samples_guitar = guitar.size
duration_guitar = n_samples_guitar/sample_freq_guitar
print('\nnumero total de amostras guitar:', n_samples_guitar)
print('duração do audio guitar (segundos):', duration_guitar)

n_samples_drums = drums.size
duration_drums = n_samples_drums/sample_freq_drums
print('\nnumero total de amostras guitar:', n_samples_guitar)
print('duração do audio drums (segundos):', duration_drums)

"""
# 4 - Selecionar segundo 12.
 
"""
sample_index = int(sample_freq_bass * 12)
audioAt = bass[sample_index:]

n_samples_audioAt = audioAt.size
duration_audioAt = n_samples_audioAt/sample_freq_bass
print('\n\nduração do audio novo audio (segundos):', duration_audioAt)

"""
# 5 - Criar uma nova variavel com audio selecionado na alınea anterior, mas repetido 4 vezes.

"""
repeatedAudio = np.tile(audioAt, 4)
print('\n\nduração do audio repetido (segundos):', getDuration(repeatedAudio, sample_freq_bass));

"""
# 6 -Seleccione os ´audios ’bass.wav’, ’guitar.wav’, ’drums.wav’ entre o segundo 10 e o segundo 20 e
cria novas vari´aveis (rum seg, guitar seg e bass seg ) com cada uma das sele¸c˜oes.
"""
sample_index_low = int(sample_freq_bass * 10)
sample_index_high = int(sample_freq_bass * 20)

audioLimited = bass[sample_index_low : sample_index_high]
print('\n\nduração do audio limitado entre 10 e 20 (segundos):', getDuration(audioLimited, sample_freq_bass));

"""
# 7 - Represente o audio 
"""
#drawAudio(bass, sample_freq_bass)

"""
#8 - Represente cada um dos sons alterando a frequencia para o dobro.

"""
#drawAudio(bass, sample_freq_bass * 2)

"""
#9 - Aumente as amplitudes do segmento bass seg (ex. bass seg*2). Represente o resultado.

"""
#drawAudio(bass * 2, sample_freq_bass)

"""
#10 - Diminuir as amplitudes do segmento bass seg (ex. bass seg*0.15). Represente o resultado.
"""
#drawAudio(bass * 0.15, sample_freq_bass)

"""
#11 -  Combine os ´audios drum seg e guitar seg (drum seg+guitar seg). Represente o resultado

"""
#drawAudio(bass + guitar, sample_freq_bass)

"""
#12 - Combine os 3 audio (drum seg+guitar seg+bass seg). Represente o resultado

"""
#drawAudio(bass + guitar + drum, sample_freq_bass)

"""
#13 - Fa¸ca uma nova combina¸c˜ao com os trˆes segmentos, mas com as novas amplitudes alteradas
nas al´ıneas anteriores.
 
"""
#drawAudio((bass + guitar + drum) * 0.15, sample_freq_bass)
#drawAudio((bass + guitar + drum) * 2, sample_freq_bass)

"""
#14 Verifique como ficam os plots de cada um dos ´audios criados na al´ınea anterior
 
"""

"""
#15 Use a rampa definida abaixo para alterar o segmento drum de forma a come¸car mais fraco e
ir aumentando de potˆencia. Para isso pode multiplicar a rampa pelo seu segmento do drum.
Fa¸ca o plot do segmento antes e depois de multiplicar pela rampa. Use este novo drum para
efetuar uma nova combina¸c˜ao dos trˆes segmentos.

"""
ramp = np.arange(0,1,1/(sample_freq_drums*10))
time = np.linspace(0, duration_drums, num=np.size(ramp))
plt.figure(figsize=(15, 5))
plt.plot(time, ramp)
plt.title('Ramp')
plt.ylabel('signal wave')
plt.xlabel('time (s)')

plt.show()

"""
16. Crie ´audios em est´ereo.

"""

stereoAudio = np.vstack((drums))