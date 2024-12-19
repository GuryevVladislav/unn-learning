import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import shutil
import os

RESULTS_DIR = "..\\results\\"
RESULTS_IMAGE_DIR = "..\\results_image"
EPSILON = 0.5e-6  # Определяем эпсилон как константу

def create_plots(df, name, n, output_dir, plot_type):
    """Создает графики на основе DataFrame."""
    x_col = 'x'
    if plot_type == "task":
        y1_col = 'v'
        y2_col = 'x2'
        y3_col = 'v2'
        y_label = 'v, v2'
        title = f'Графики v(x) и v2(x) для задачи: {name}, n: {n}'
        filename = f'graph_{name}_{n}.png'
    elif plot_type == "test":
        y1_col = 'v'
        y2_col = 'x'
        y3_col = 'u'
        y_label = 'v, u'
        title = f'Графики v(x) и u(x) для задачи: {name}, n: {n}'
        filename = f'graph_vu_{name}_{n}.png'
    else:
        raise ValueError("Неверный тип графика")

    # График y1(x) и y3(x)
    plt.figure(figsize=(8, 6))
    plt.plot(df[x_col], df[y1_col], marker='o', linestyle='-', label=f'{y1_col}({x_col})')
    plt.plot(df[x_col], df[y3_col], marker='s', linestyle='--', label=f'{y3_col}({x_col})')
    plt.xlabel(x_col)
    plt.ylabel(y_label)
    plt.title(title)
    plt.grid(True)
    plt.legend()
    plt.savefig(os.path.join(output_dir, filename))
    plt.close()

    # График x от diff
    plt.figure(figsize=(8, 6))
    plt.plot(df[x_col], df['diff'], marker='x', linestyle='', label='diff(x)')
    plt.xlabel(x_col)
    plt.ylabel('diff')
    plt.title(f'График diff(x) для задачи: {name}, n: {n}')
    plt.grid(True)
    plt.legend()
    plt.savefig(os.path.join(output_dir, f'graph_diff_{name}_{n}.png'))
    plt.close()

def create_table(df, name, n, output_dir):
    """Создает таблицу."""
    plt.figure(figsize=(12, max(8, n * 0.35)))
    plt.axis('off')
    table = plt.table(cellText=df.values, colLabels=df.columns, loc='center')
    table.auto_set_font_size(True)
    table.set_fontsize(20)
    table.scale(1, 2)
    plt.savefig(os.path.join(output_dir, f'table_{name}_{n}.png'))
    plt.close()

def create_text_results(name, n, max_diff, max_x, output_dir, task_type):
    """Создает текстовый файл с результатами."""
    output_text_filepath = os.path.join(output_dir, f'results_{name}_{n}.txt')
    with open(output_text_filepath, 'w', encoding='utf-8') as text_file:
        text_file.write(f"Для решения задачи использована равномерная сетка с числом разбиений n = {n};\n")
        text_file.write(f"Задача должна быть решена с заданной точностью ε = {EPSILON:.1e};\n")
        epsilon_label = "ε2" if task_type == "task" else "ε1"
        text_file.write(f"Задача решена с точностью {epsilon_label} = {max_diff:.2e};\n")
        text_file.write(f"Максимальная разность численных решений в общих узлах сетки наблюдается в точке x = {max_x}")

def process_data(filepath_results, filepath_input, output_dir):
    """Обрабатывает данные, создает DataFrame и сохраняет результаты."""
    try:
        os.makedirs(output_dir, exist_ok=True)

        with open(filepath_input, 'r', encoding='utf-8') as f:
            name, n_str = f.readline().split()
            n = int(n_str)

        print(f"Имя задачи: {name}, n: {n}")

        data = np.loadtxt(filepath_results, skiprows=0)

        if name.lower() == "task":
            df = pd.DataFrame(data, columns=['i', 'x', 'v', 'x2', 'v2', 'diff'])
            plot_type = "task"
        elif name.lower() == "test":
            df = pd.DataFrame(data, columns=['i', 'x', 'v', 'u', 'diff'])
            plot_type = "test"
        else:
            raise ValueError("Неизвестное имя задачи в input.txt")

        print("DataFrame:")
        print(df)

        max_diff = df['diff'].abs().max()
        max_diff_index = df['diff'].abs().idxmax()
        max_x = df['x'][max_diff_index]

        create_plots(df, name, n, output_dir, plot_type)
        create_table(df, name, n, output_dir)
        create_text_results(name, n, max_diff, max_x, output_dir, plot_type)

    except FileNotFoundError:
        print("Один или оба файла не найдены.")
    except ValueError as e:
        print(f"Ошибка при чтении данных: {e}. Проверьте формат и кодировку файлов (UTF-8).")
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

    filepath_results = os.path.join(RESULTS_DIR, "results.txt")
    filepath_input = os.path.join(RESULTS_DIR, "input.txt")
    output_directory = RESULTS_IMAGE_DIR
    process_data(filepath_results, filepath_input, output_directory)