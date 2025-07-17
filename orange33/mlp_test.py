import numpy as np
import pandas as pd
from sklearn.metrics import accuracy_score
from sklearn.neural_network import MLPClassifier

df = pd.read_csv("/home/aa/kuBig2025/orange33/healthcare-dataset-3.csv")
print(df.shape)
print(df.info())
print(df.columns)
clf_mlp = MLPClassifier(
    hidden_layer_sizes=(100, 1000, 100), max_iter=2000, random_state=0
)

y = df[df.columns[5]]
X = df.drop(df.columns[5], axis=1)
clf_mlp.fit(X, y)
pred_y = clf_mlp.predict(X)
accuracy = accuracy_score(y, pred_y)
print(accuracy)
