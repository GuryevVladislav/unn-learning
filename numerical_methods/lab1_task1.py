import os
import pandas as pd
import matplotlib.pyplot as plt

with open("C:\\unn-learning\\results.txt", "r") as f:
 data = f.readlines()
data = [line.strip().split() for line in data]
df = pd.DataFrame(data, columns=['x', 'v', 'h' , 'k1', 'k2', 'k3', 'k4'])

df['x'] = df['x'].astype(float)
df['v'] = df['v'].astype(float)
df['h'] = df['h'].astype(float)
df['k1'] = df['k1'].astype(float)
df['k2'] = df['k2'].astype(float)
df['k3'] = df['k3'].astype(float)
df['k4'] = df['k4'].astype(float)
df.index = df.index + 1

# Создаем фигуру и оси
fig, ax = plt.subplots(figsize=(12, 8)) 

# Рисуем график v(x)
ax.plot(df['x'], df['v'], label='v(x)')
ax.set_xlabel('x')
ax.set_ylabel('v')
ax.legend()
ax.set_title('График зависимости v от x')
ax.grid(True)

# Добавляем таблицу под графиком
table = ax.table(
  cellText=df.values, 
  colLabels=df.columns, 
  loc='bottom', # Расположение таблицы под графиком
  bbox=[0.2, -0.5, 0.6, 0.3] # Позиционирование таблицы
)

# Устанавливаем стиль таблицы (по желанию)
table.set_fontsize(10)
table.auto_set_font_size(False)
table.scale(1.2, 1.2)

# Проверяем существование файла и удаляем его, если он есть
filename = "table_and_graph.png"
if os.path.exists(filename):
  os.remove(filename)

# Сохраняем изображение
plt.savefig(filename, bbox_inches='tight')
print("График и таблица сохранены в ", filename)
