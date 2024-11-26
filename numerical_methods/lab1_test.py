import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# --- Конфигурация ---
RESULTS_DIR = "C:\\unn-learning\\numerical_methods\\results\\"
FILES_TO_REMOVE = [RESULTS_DIR + "graph.png", RESULTS_DIR + "table.png", RESULTS_DIR + "input_parameters.png"]

def read_params(filepath):
  """Читает параметры из файла."""
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
  except (ValueError, IndexError) as e:
    raise ValueError(f"Ошибка при разборе файла {filepath}: {e}")

def read_results(filepath):
  """Читает результаты из файла."""
  try:
    with open(filepath, "r") as f:
      data = f.readlines()
      return [line.strip().split() for line in data if line.strip()]
  except FileNotFoundError:
    raise FileNotFoundError(f"Файл {filepath} не найден.")
  except Exception as e:
    raise Exception(f"Ошибка при чтении файла {filepath}: {e}")

def create_dataframe(data):
  """Создает DataFrame из данных."""
  df = pd.DataFrame(data, columns=['i', 'x', 'v', 'v2', 'v-v2', 'OLP', 'h', 'c1', 'c2', 'u', '|u-v|'])
  for col in df.columns:
    df[col] = pd.to_numeric(df[col], errors='coerce')
  df.index = df.index + 1
  return df

def save_plot(filepath, x_data, y_data, title, xlabel, ylabel, extra_line=None):
  """Сохраняет график в файл."""
  fig, ax = plt.subplots(figsize=(12, 8))
  ax.plot(x_data, y_data, label='v(x)')
  if extra_line:
    x, y, label = extra_line
    ax.plot(x, y, linestyle='--', label=label)
  ax.set_xlabel(xlabel)
  ax.set_ylabel(ylabel)
  ax.legend()
  ax.set_title(title)
  ax.grid(True)
  plt.tight_layout()
  plt.savefig(filepath, bbox_inches='tight')
  plt.close(fig)

def save_table(filepath, data, columns, figsize=(12, 8), scale=1.2):
  """Сохраняет таблицу в файл."""
  fig, ax = plt.subplots(figsize=figsize)
  table = ax.table(
    cellText=data.values,
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

def save_params_table(filepath, params):
  """Сохраняет таблицу параметров."""
  params_df = pd.DataFrame({"Parameter": params.keys(), "Value": params.values()})
  save_table(filepath, params_df, params_df.columns, figsize=(6, 2), scale=1.5)

if __name__ == "__main__":
  try:
    for filename in FILES_TO_REMOVE:
      if os.path.exists(filename):
        os.remove(filename)

    params = read_params(RESULTS_DIR + "initial_params.txt")
    n = params["n"]
    v0 = params["v0"]
    results_data = read_results(RESULTS_DIR + "results.txt")
    df = create_dataframe(results_data)

    x_values = np.linspace(df['x'].min(), df['x'].max(), 100)
    y_values = v0 * np.exp(x_values)
    extra_line = (x_values, y_values, rf'y = {v0:.2f}e$^x$') # используем rf-строку для LaTeX

    save_plot(RESULTS_DIR + "graph.png", df['x'], df['v'], 'График зависимости v от x', 'x', 'v', extra_line=extra_line)
    save_table(RESULTS_DIR + "table.png", df, df.columns, figsize=(12, max(8, n * 0.3)))
    save_params_table(RESULTS_DIR + "input_parameters.png", params)

  except (FileNotFoundError, ValueError, Exception) as e:
    print(f"Ошибка: {e}")
