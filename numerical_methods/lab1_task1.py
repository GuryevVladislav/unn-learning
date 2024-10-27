import pandas as pd
import matplotlib.pyplot as plt

with open("D:\\unn-learning\\numerical_methods\\results.txt", "r") as f:
  data = f.readlines()
data = [line.strip().split() for line in data]
df = pd.DataFrame(data, columns=['x', 'v', 'k1', 'k2', 'k3', 'k4'])

df['x'] = df['x'].astype(float)
df['v'] = df['v'].astype(float)
df['k1'] = df['k1'].astype(float)
df['k2'] = df['k2'].astype(float)
df['k3'] = df['k3'].astype(float)
df['k4'] = df['k4'].astype(float)
df.index = df.index + 1

plt.figure(figsize=(12, 6))
plt.table(cellText=df.values, colLabels=df.columns, loc='center')
plt.axis('off') 

plt.savefig("table_image.png")
plt.show()
