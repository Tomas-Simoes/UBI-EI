"""
4) Bitmap guardam informações baseadas em pixeis
incluindo cor, dimensão, profundidade etc...

Vetorial guarda informação baseadas em formas geometricas
com caminhos e camadas matemáticas

5) Bitmap é facil mudar informações haver com edição de cor
efeitos visuais.

Vetorial é mais facil mudar informações que envolvem 
formas e edições estruturais.

6) Bitmap é melhor para qualidade de imagem, no entanto 
acaba por ter um tamanho maior

Vetorial é melhor para gráficos e ilustrações mas 
não são boas para imagens com grande detalhe

7) A tecnica de entrelaçamento permite que a 
imagem seja carregada em camadas em vez de cima
para baixo. Isto permite que elas sejam 
carregadas de forma progressiva, sendo mais eficiente.

8) A codificação progressiva faz com que os conversores 
e desconversores tenham de ser projetados para lidar com a informação da imagem
ao longo que elas vão sendo carregadas em camadas. Isso requer um
cuidado com os dados e que pode aumentar a complexidade
do algoritmo.

"""