# O ficheiro de dados cancro.csv contém informação de 30 medidas (atributos) relativas a um estudo do cancro da mama. Os atributos medem coisas como a
# área das lesões, a sua concavidade e simetria.
# A última coluna dos dados indica se o cancro é benigno (0) ou maligno (1).
# Vamos usar um classificador SVM para prevermos o valor desta última coluna
# dos dados. O ficheiro aval_NUMERO.py serve de template.
# Use os primeiros 300 pontos para servirem de conjunto de treino e os restantes
# para servirem de conjunto de teste.
# Use o seu modelo para responder às seguintes questões:
# 1. Ache a taxa de erro que o classificador obtém no conjunto de teste.
# 2. Qual destes 30 atributos é o mais importante e qual é o menos importante
# para a classificação dos dados de cancro? Note que não precisa de usar
# todos os atributos quando corre o classificador.

from sklearn import svm
import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('cancro.csv', delimiter=',')

X_train = data[:300, :30]
Y_train = data[:300, 30]

X_test = data[300:, :30]
Y_test = data[300:, 30]

clf = svm.SVC(C=1000)
clf.fit(X_train, Y_train)

accuracy = clf.score(X_test, Y_test)
error = 1 - accuracy

clf = svm.SVC(C=1000, kernel="linear")
clf.fit(X_train, Y_train)

importances = np.abs(clf.coef_[0])
most_important = np.argmax(importances)
less_important = np.argmin(importances)