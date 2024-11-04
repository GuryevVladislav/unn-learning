import os
import pandas as pd
import matplotlib.pyplot as plt

with open("D:\\unn-learning\\results.txt", "r") as f:
 data = f.readlines()
data = [line.strip().split() for line in data]
df = pd.DataFrame(data, columns=['i','x', 'v', 'v2', 'v-v2', 'OLP', 'h', 'c1', 'c2'])

df['i'] = df['i'].astype(int)
df['x'] = df['x'].astype(float)
df['v'] = df['v'].astype(float)
df['v2'] = df['v2'].astype(float)
df['v-v2'] = df['v-v2'].astype(float)
df['OLP'] = df['OLP'].astype(float)
df['h'] = df['h'].astype(float)
df['c1'] = df['c1'].astype(int)
df['c2'] = df['c2'].astype(int)
df.index = df.index + 1


fig, ax = plt.subplots(figsize=(12, 8)) 
ax.plot(df['x'], df['v'], label='v(x)')
ax.set_xlabel('x')
ax.set_ylabel('v')
ax.legend()
ax.set_title('График зависимости v от x')
ax.grid(True)

table = ax.table(
  cellText=df.values, 
  colLabels=df.columns, 
  loc='bottom',
  bbox=[0.0, -0.5, 1.0, 0.3]
)

table.set_fontsize(10)
table.auto_set_font_size(False)
table.scale(1.2, 1.2)

filename = "table_and_graph.png"
if os.path.exists(filename):
  os.remove(filename)

plt.savefig(filename, bbox_inches='tight')
print("График и таблица сохранены в ", filename)

