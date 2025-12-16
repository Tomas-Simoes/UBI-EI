
import numpy as np 
import matplotlib.pyplot as plt

from sklearn import tree
from sklearn.datasets import load_iris
from sklearn.model_selection import ShuffleSplit, cross_val_score

data = np.loadtxt('regression.txt')
X = data[:, 0:21]
Y = data[:, 21]

X_test = X[:126]
Y_test = Y[:126]

X_training = X[126:]
Y_training = Y[126:]

def slice_training():
    for slice in [100, 200, 500, 1000, 2000]:
        X_slice = X_training[:slice]
        Y_slice = Y_training[:slice]

        clf = tree.DecisionTreeClassifier()
        clf.fit(X_slice, Y_slice)

        accuracy = clf.score(X_test, Y_test)
        print(f"Training size: {slice}, Test accuracy: {accuracy}")
        
def fold_corss_training():
    cv = ShuffleSplit(n_splits=10)
    
    clf = tree.DecisionTreeClassifier()
    scores = cross_val_score(clf, X, Y, cv=cv)

    print(f"Avg accuracy: {scores.mean():.3f}")
    print(f"Accuracy per fold: {scores}")

fold_corss_training()