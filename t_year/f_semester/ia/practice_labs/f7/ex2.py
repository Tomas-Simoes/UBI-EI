import numpy as np
from sklearn.linear_model import LinearRegression

data = np.loadtxt("size_price.csv", delimiter=",")

X = data[:, 0].reshape(-1, 1)
y = data[:, 1]

model = LinearRegression()
model.fit(X, y)

predicted_price = model.predict([[350]])
print(f"Estimated price for 350 m²: {predicted_price[0]:.2f}")