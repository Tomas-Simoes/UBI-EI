import numpy as np
from sklearn import svm
import matplotlib.pyplot as plt

data = np.loadtxt("espiral_train.csv", delimiter=",")
test = np.loadtxt("espiral_test.csv", delimiter=",")

X_train = data[:, 0:2]
Y_train = data[:, 2]

X_test = test[:, 0:2]
Y_test = test[:, 2]

def run_svm():
    C_values = [1, 5, 10, 50, 100, 500, 1000]
    ACC_values = []
    for C in [1, 5, 10, 50, 100, 500, 1000]:
        clf = svm.SVC(C=C)
        clf.fit(X_train,Y_train)

        accuracy = clf.score(X_test, Y_test)
        generalization_error = 1 - accuracy
        
        ACC_values.append(accuracy)

        print(f"Test accuracy: {accuracy:.3f}")
        print(f"Generalization error: {generalization_error:.3f}")

    plt.plot(C_values, ACC_values)
    plt.xlabel("C_values")
    plt.ylabel("Accuracy")
    plt.show()


def run_naive_bayes():
    classes = np.unique(Y_train)

    means = {}
    variances = {}
    priors = {}

    for c in classes:
        X_c = X_train[Y_train == c]
        means[c] = np.mean(X_c, axis=0)
        variances[c] = np.var(X_c, axis=0)
        priors[c] = X_c.shape[0] / X_train.shape[0]

    def gaussian(x, mean, var):
        return (1.0 / np.sqrt(2 * np.pi * var)) * np.exp(- (x - mean) ** 2 / (2 * var))
    
    def predict(X):
        predictions = []

        for x in X:
            posteriors = []

            for c in classes:
                likelihood = gaussian(x, means[c],variances[c])
                posterior = np.sum(np.log(likelihood)) + np.log(priors[c])
                posteriors.append(posterior)

            predictions.append(classes[np.argmax(posteriors)])

        return np.array(predict)
    
    Y_pred = predict(X_test)

    accuracy = np.mean(Y_pred == Y_test)
    generalization_error = 1 - accuracy

    print(f"Test accuracy: {accuracy:.3f}")
    print(f"Generalization error: {generalization_error:.3f}")

def run_knn():
    

    def euclidean_dist(x1, x2): return np.sqrt(np.sum((x1 - x2)**2))

    def run_knn_one(x, X_train, Y_train, k):
        distances = []

        for i in range(len(X_train)):
            distances.append(euclidean_dist(x, X_train[i]))
        
        distances = np.argsort(distances)
        votes = {}

        for i in range(k):
            label = Y_train[distances[i]]
            votes[label] = votes.get(label, 0) + 1

        return max(votes, key=votes.get)
    
    for k in [1,7]:
        prediction = []

        for x in X_test: 
            prediction.append(run_knn_one(x, X_train, Y_train, k))
        
        Y_pred = np.array(prediction)
            
        accuracy = np.mean(Y_pred == Y_test)
        generalization_error = 1 - accuracy

        print(f"k = {k}")
        print(f"Test accuracy: {accuracy:.3f}")
        print(f"Generalization error: {generalization_error:.3f}")


run_knn()