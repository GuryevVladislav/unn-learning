import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Удаляем предыдущие файлы, если они существуют
if os.path.exists("graph.png"):
  os.remove("graph.png")
if os.path.exists("table.png"):
  os.remove("table.png")

with open("numerical_methods\\results\\results.txt", "r") as f:
  data = f.readlines()
data = [line.strip().split() for line in data]
df = pd.DataFrame(data, columns=['i','x', 'v', 'v2', 'v-v2', 'OLP', 'h', 'c1', 'c2', 'u','|u-v|'])

df['i'] = df['i'].astype(float)
df['x'] = df['x'].astype(float)
df['v'] = df['v'].astype(float)
df['v2'] = df['v2'].astype(float)
df['v-v2'] = df['v-v2'].astype(float)
df['OLP'] = df['OLP'].astype(float)
df['h'] = df['h'].astype(float)
df['c1'] = df['c1'].astype(float)
df['c2'] = df['c2'].astype(float)
df['u'] = df['u'].astype(float)
df['|u-v|'] = df['|u-v|'].astype(float)
df.index = df.index + 1

# Ввод значения 'a' с клавиатуры
a = float(input("Введите значение 'a': "))
h = float(input("Введите количество шагов: "))

# --- Сохранение графика ---

fig, ax = plt.subplots(figsize=(12, 8)) # Размер по умолчанию

# Вывод графика v(x)
ax.plot(df['x'], df['v'], label='v(x)')

# Вывод графика y=a*e^x
x_values = np.linspace(df['x'].min(), df['x'].max(), 100)
y_values = a * np.exp(x_values)
ax.plot(x_values, y_values, label=f'y = {a:.2f}e^x', linestyle='--')

# Настройка графика
ax.set_xlabel('x')
ax.set_ylabel('v')
ax.legend()
ax.set_title('График зависимости v от x и y = ae^x')
ax.grid(True)

plt.tight_layout() # Удаляем ненужные отступы

filename_graph = "graph.png"
if os.path.exists(filename_graph):
  os.remove(filename_graph)

plt.savefig(filename_graph, bbox_inches='tight')
print("График сохранен в ", filename_graph)
plt.close(fig) # Закрываем окно графика

# --- Сохранение таблицы ---

fig, ax = plt.subplots(figsize=(12, h/2)) # Создаем новый рисунок

# Создаем таблицу
table = ax.table(
  cellText=df.values[:110], # Вывод только первых 110 строк
  colLabels=df.columns,
  loc='center', 
  bbox=[0.0, 0.0, 1.0, 1.0] # Заполняем все пространство рисунка
)

table.set_fontsize(10)
table.auto_set_font_size(False)
table.scale(1.5, 1.5) # Увеличиваем масштаб таблицы

ax.axis('off') # Убираем оси
plt.tight_layout() # Удаляем ненужные отступы

filename_table = "table.png"
if os.path.exists(filename_table):
  os.remove(filename_table)

plt.savefig(filename_table, bbox_inches='tight')
print("Таблица сохранена в ", filename_table)
plt.close(fig) # Закрываем окно таблицы