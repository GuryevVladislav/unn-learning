import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import shutil

# --- Конфигурация ---
RESULTS_DIR = "D:\\unn-learning\\numerical_methods\\results\\"
RESULTS_IMAGE_DIR = "D:\\unn-learning\\numerical_methods\\results_image"

def read_initial_params(filepath):
  """Читает начальные параметры из файла."""
  try:
    with open(filepath, "r") as f:
      params = f.readline().strip().split()
      return {
        "n": int(params[0]),
        "e": float(params[1]),
        "b": float(params[2]),
        "v0": float(params[3]),
      }
  except FileNotFoundError:
    raise FileNotFoundError(f"Файл {filepath} не найден.")

def read_results(filepath):
  """Читает результаты из файла."""
  try:
    with open(filepath, "r") as f:
      data = f.readlines()
      return [line.strip().split() for line in data if line.strip()]
  except FileNotFoundError:
    raise FileNotFoundError(f"Файл {filepath} не найден.")

def create_dataframe(data):
  """Создает DataFrame из данных."""
  try:
    df = pd.DataFrame(data, columns=['i', 'x', 'v', 'v2', 'v-v2', 'OLP', 'h', 'c1', 'c2', "v'"])
    for col in df.columns:
      df[col] = pd.to_numeric(df[col], errors='coerce')
    df.index = df.index + 1
    return df
  except ValueError as e:
    print(f"Ошибка при создании DataFrame: {e}. Возможно, не хватает данных в файле results.txt")
    return None # Возвращаем None, чтобы показать, что создание DataFrame не удалось.

def save_plot(filepath, x_data, y_data, title, xlabel, ylabel):
  """Сохраняет график в файл."""
  try:
    fig, ax = plt.subplots(figsize=(12, 8))
    ax.plot(x_data, y_data, label='v(x)')
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.legend()
    ax.set_title(title)
    ax.grid(True)
    plt.tight_layout()
    plt.savefig(filepath, bbox_inches='tight')
    plt.close(fig)
    print(f"График сохранен в '{filepath}'")
  except Exception as e:
    print(f"Ошибка при сохранении графика '{filepath}': {e}")


def save_table(filepath, data, columns, figsize=(12, 8), scale=1.2):
  """Сохраняет таблицу в файл."""
  try:
    fig, ax = plt.subplots(figsize=figsize)
    table = ax.table(
        cellText=data[columns].values, # Изменение: выбираем только нужные столбцы
        colLabels=columns,
        loc='center',
        bbox=[0.0, 0.0, 1.0, 1.0]
    )
    table.set_fontsize(10)
    table.auto_set_font_size(False)
    table.scale(scale, scale)
    ax.axis('off')
    plt.tight_layout()
    plt.savefig(filepath, bbox_inches='tight')
    plt.close(fig)
    print(f"Таблица сохранена в '{filepath}'")
  except Exception as e:
    print(f"Ошибка при сохранении таблицы '{filepath}': {e}")



def save_params_table(filepath, params):
  """Сохраняет таблицу параметров в файл."""
  params_df = pd.DataFrame({"Parameter": list(params.keys()), "Value": list(params.values())})
  save_table(filepath, params_df, params_df.columns, figsize=(6, 2), scale=1.5)


# --- Основная программа ---
try:
  shutil.rmtree(RESULTS_IMAGE_DIR)  # Попытка удалить, если существует
  print(f"Папка '{RESULTS_IMAGE_DIR}' удалена.")
except FileNotFoundError:
  print(f"Папка '{RESULTS_IMAGE_DIR}' не найдена. Пропускаем удаление.")
except OSError as e:
  print(f"Ошибка при удалении папки '{RESULTS_IMAGE_DIR}': {e}")

try:
  os.makedirs(RESULTS_IMAGE_DIR, mode=0o755, exist_ok=True) # Создаем папку, exist_ok=True предотвращает ошибку, если папка уже существует
  print(f"Папка '{RESULTS_IMAGE_DIR}' создана.")
except OSError as e:
  print(f"Ошибка при создании папки '{RESULTS_IMAGE_DIR}': {e}")

try:
  initial_params = read_initial_params(RESULTS_DIR + "initial_params.txt")
  n = initial_params["n"]
  results_data = read_results(RESULTS_DIR + "results.txt")
  df = create_dataframe(results_data)

  if df is not None:
        save_plot(RESULTS_IMAGE_DIR + "/graph_x_v.png", df['x'], df['v'], 'График зависимости v от x', 'x', 'v')
        save_plot(RESULTS_IMAGE_DIR + "/graph_v_v_pr.png", df['v'], df["v'"], "График зависимости v от v'", 'v', "v'")
        save_plot(RESULTS_IMAGE_DIR + "/graph_x_v_pr.png", df['x'], df["v'"], "График зависимости x от v'", 'x', "v'")
        columns_to_save = ['i', 'x', 'v', 'v2', 'v-v2', 'OLP', 'h', 'c1', 'c2'] # Столбцы для сохранения
        save_table(RESULTS_IMAGE_DIR + "/table.png", df, columns_to_save, figsize=(12, max(8, n * 0.3)))
  else:
    print("Не удалось создать DataFrame. Сохранение графиков и таблиц пропущено.")

except FileNotFoundError as e:
  print(f"Ошибка: {e}")
except Exception as e:
  print(f"Произошла непредвиденная ошибка: {e}")
