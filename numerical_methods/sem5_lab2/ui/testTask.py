import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import shutil
import os

RESULTS_DIR = "..\\results"
RESULTS_IMAGE_DIR = "..\\results_image"

def process_data(filepath_results, filepath_input, output_dir):
    """
    Считывает данные, создает DataFrame, графики, таблицу и текстовый файл с результатами.
    """
    try:
        os.makedirs(output_dir, exist_ok=True)

        with open(filepath_input, 'r', encoding='utf-8') as f:
            line = f.readline()
            parts = line.split()
            if len(parts) != 2:
                raise ValueError("Неверный формат файла input.txt. Ожидается 'имя n'")
            name, n_str = parts
            n = int(n_str)

        print(f"Имя задачи: {name}, n: {n}")

        if name.lower() != "test":  # Проверка имени задачи
            print("Имя задачи не 'test'. Завершение работы.")
            return

        data = np.loadtxt(filepath_results, skiprows=0)
        df = pd.DataFrame(data, columns=['i', 'x', 'v', 'u', 'diff'])
        print("DataFrame:")
        print(df)

        # Находим максимальную разность и соответствующее x
        max_diff = df['diff'].abs().max()
        max_diff_index = df['diff'].abs().idxmax()
        max_x = df['x'][max_diff_index]

        # График v(x) и u(x)
        plt.figure(figsize=(8, 6))
        plt.plot(df['x'], df['v'], marker='o', linestyle='-', label='v(x)')
        plt.plot(df['x'], df['u'], marker='s', linestyle='--', label='u(x)')
        plt.xlabel('x')
        plt.ylabel('v, u')
        plt.title(f'Графики v(x) и u(x) для задачи: {name}, n: {n}')
        plt.grid(True)
        plt.legend()
        plt.savefig(os.path.join(output_dir, f'graph_vu_{name}_{n}.png'))
        plt.close()

        # График x от diff - только точки
        plt.figure(figsize=(8, 6))
        plt.plot(df['x'], df['diff'], marker='x', linestyle='', label='diff(x)')
        plt.xlabel('x')
        plt.ylabel('diff')
        plt.title(f'График diff(x) для задачи: {name}, n: {n}')
        plt.grid(True)
        plt.legend()
        plt.savefig(os.path.join(output_dir, f'graph_diff_{name}_{n}.png'))
        plt.close()

        # Таблица
        plt.figure(figsize=(12, max(8, n * 0.35)))
        plt.axis('off')
        table = plt.table(cellText=df.values, colLabels=df.columns, loc='center')
        table.auto_set_font_size(True)
        table.set_fontsize(20)
        table.scale(1, 2)
        plt.savefig(os.path.join(output_dir, f'table_{name}_{n}.png'))
        plt.close()

        # Создание текстового файла с результатами
        output_text_filepath = os.path.join(output_dir, f'results_{name}_{n}.txt')
        with open(output_text_filepath, 'w', encoding='utf-8') as text_file:
            text_file.write(f"Для решения задачи использована равномерная сетка с числом разбиений n = {n};\n")
            text_file.write(f"Задача должна быть решена с заданной точностью ε = 0.5⋅10⁻⁶;\n")
            text_file.write(f"Задача решена с точностью ε1 = {max_diff:.2e};\n")
            text_file.write(f"Максимальная разность численных решений в общих узлах сетки наблюдается в точке x = {max_x};")

    except FileNotFoundError:
        print("Один или оба файла не найдены.")
    except ValueError as e:
        print(f"Ошибка при чтении данных: {e}. Проверьте формат файлов и кодировку (UTF-8).")
    except Exception as e:
        print(f"Произошла ошибка: {e}")


if __name__ == "__main__":
    filepath_results = RESULTS_DIR+"\\results.txt"
    filepath_input = RESULTS_DIR+"\\input.txt"
    output_directory = RESULTS_IMAGE_DIR

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

    process_data(filepath_results, filepath_input, output_directory)
