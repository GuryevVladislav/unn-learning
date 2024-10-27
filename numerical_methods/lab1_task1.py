import pandas as pd
import matplotlib.pyplot as plt

# Чтение данных из файла txt
with open("D:\\unn-learning\\numerical_methods\\results.txt", "r") as f:
  data = f.readlines()

# Обработка данных
data = [line.strip().split() for line in data]

# Создание DataFrame
df = pd.DataFrame(data, columns=['x', 'v', 'k1', 'k2', 'k3', 'k4'])

# Преобразование типов данных
df['x'] = df['x'].astype(float)
df['v'] = df['v'].astype(float)
df['k1'] = df['k1'].astype(float)
df['k2'] = df['k2'].astype(float)
df['k3'] = df['k3'].astype(float)
df['k4'] = df['k4'].astype(float)

# Изменение индекса
df.index = df.index + 1


# Создание графика таблицы
plt.figure(figsize=(12, 6)) # Установите желаемый размер изображения
plt.table(cellText=df.values, colLabels=df.columns, loc='center')
plt.axis('off') # Удаление осей

# Сохранение изображения
plt.savefig("table_image.png") # Замените "table_image.png" на желаемое имя файла

# Отображение изображения (опционально)
plt.show()
