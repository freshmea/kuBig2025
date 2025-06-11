import numpy as np
import pandas as pd
from Orange.data import ContinuousVariable, DiscreteVariable, Domain, Table

df = pd.DataFrame(in_data)
df = df.drop(0, axis=1)
df = df.replace(True, 1).replace(False, "")
ydf = pd.DataFrame(index=df.index)
mdf = pd.DataFrame(index=df.index)

out_data = Table.from_pandas_dfs(df, ydf, mdf)
