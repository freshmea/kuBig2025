import numpy as np
import pandas as pd
from Orange.data import ContinuousVariable, DiscreteVariable, Domain, Table

X_df, y_df, m_df = in_data.to_pandas_dfs()
X_df = pd.get_dummies(X_df, columns=[X_df.columns[1]])
X_df = pd.get_dummies(X_df, columns=[X_df.columns[1]])
X_df = pd.get_dummies(X_df, columns=[X_df.columns[3]])

out_data = Table.from_pandas_dfs(X_df, y_df, m_df)
