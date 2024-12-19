import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import shutil
import os

RESULTS_DIR = "D:\\unn-learning\\numerical_methods\\sem5_lab2\\results\\"
RESULTS_IMAGE_DIR = "D:\\unn-learning\\numerical_methods\\sem5_lab2\\results_image"

def process_data(filepath_results, filepath_input, output_dir):
    """
    Считывает данные, создает DataFrame и сохраняет график и таблицу в указанную директорию.
    """
    try:
        os.makedirs(output_dir, exist_ok=True)

        with open(filepath_input, 'r') as f:
            name, n_str = f.readline().split()
            n = int(n_str)

        print(f"Имя задачи: {name}, n: {n}")

        data = np.loadtxt(filepath_results, skiprows=0)
        df = pd.DataFrame(data, columns=['i', 'x', 'v', 'x2', 'v2', 'diff'])
        print("DataFrame:")
        print(df)

        # График - v(x) and v2(x)
        plt.figure(figsize=(8, 6))
        plt.plot(df['x'], df['v'], marker='o', linestyle='-', label='v(x)')
        plt.plot(df['x2'], df['v2'], marker='s', linestyle='--', label='v2(x)') # Added v2(x) plot
        plt.xlabel('x')
        plt.ylabel('v, v2')  # Updated y-label
        plt.title(f'Графики v(x) и v2(x) для задачи: {name}, n: {n}') # Updated title
        plt.grid(True)
        plt.legend()
        plt.savefig(os.path.join(output_dir, f'graph_{name}_{n}.png'))
        plt.close()

        # Таблица (unchanged)
        plt.figure(figsize=(12, max(8, n / 2.)))
        plt.axis('off')
        table = plt.table(cellText=df.values, colLabels=df.columns, loc='center')
        table.auto_set_font_size(True)
        table.set_fontsize(20)
        table.scale(1, 2)
        plt.savefig(os.path.join(output_dir, f'table_{name}_{n}.png'))
        plt.close()

    except FileNotFoundError:
        print("Один или оба файла не найдены.")
    except ValueError:
        print("Ошибка при чтении данных из input.txt. Проверьте формат файла.")
    except Exception as e:
        print(f"Произошла ошибка: {e}")


if __name__ == "__main__":
    try:
        shutil.rmtree(RESULTS_IMAGE_DIR)
        print(f"Папка '{RESULTS_IMAGE_DIR}' удалена.")
    except FileNotFoundError:
        print(f"Папка '{RESULTS_IMAGE_DIR}' не найдена. Пропускаем удаление.")
    except OSError as e:
        print(f"Ошибка при удалении папки '{RESULTS_IMAGE_DIR}': {e}")
    try:
        os.makedirs(RESULTS_IMAGE_DIR, mode=0o755, exist_ok=True)
        print(f"Папка '{RESULTS_IMAGE_DIR}' создана.")
    except OSError as e:
        print(f"Ошибка при создании папки '{RESULTS_IMAGE_DIR}': {e}")
    filepath_results = "D:\\unn-learning\\numerical_methods\\sem5_lab2\\results\\results.txt"
    filepath_input = "D:\\unn-learning\\numerical_methods\\sem5_lab2\\results\\input.txt"
    output_directory = RESULTS_IMAGE_DIR
    process_data(filepath_results, filepath_input, output_directory)
