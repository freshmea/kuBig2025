import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

data = pd.read_csv("/home/aa/kuBig2025/orange33/basket_analysis.csv")
corr = data.corr()
print(corr)

sns.heatmap(corr, annot=True, cmap="coolwarm", vmin=-1, vmax=1)
plt.show()

from Orange.data import Table

Table.to
