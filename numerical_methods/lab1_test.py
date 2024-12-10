import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import shutil

RESULTS_DIR = "D:\\unn-learning\\numerical_methods\\results\\"
RESULTS_IMAGE_DIR = "D:\\unn-learning\\numerical_methods\\results_image\\"

def process_results(filepath):
    """Читает, обрабатывает и возвращает данные из файла results.txt.
       Обрабатывает ошибки чтения файла и преобразования типов."""
    try:
        with open(filepath, "r") as f:
            data = f.readlines()
    except FileNotFoundError:
        print(f"Ошибка: Файл не найден по адресу {filepath}")
        return None

    data = [line.strip().split() for line in data]
    df = pd.DataFrame(data, columns=['i','x', 'v', 'v2', 'v-v2', 'OLP', 'h', 'c1', 'c2', 'u','|u-v|'])
    for col in df.columns:
        try:
            df[col] = df[col].astype(float)
        except ValueError:
            print(f"Предупреждение: Не удалось преобразовать столбец '{col}' в числовой тип. Проверьте файл данных.")
            return None

    df.index = df.index + 1
    return df


def plot_results(df,filename, a):
    """Строит и сохраняет график."""
    fig, ax = plt.subplots(figsize=(12, 8))

    ax.plot(df['x'], df['v'], label='v(x)')
    x_values = np.linspace(df['x'].min(), df['x'].max(), 100)
    y_values = a * np.exp(x_values)
    ax.plot(x_values, y_values, label=f'y = {a:.2f}e^x', linestyle='--')

    ax.set_xlabel('x')
    ax.set_ylabel('v')
    ax.legend()
    ax.set_title('График зависимости v от x и y = ae^x')
    ax.grid(True)
    plt.tight_layout()
    plt.savefig(filename, bbox_inches='tight')
    plt.close(fig)


def create_table(df, n, filename, rows_to_show=None):
    """Создаёт и сохраняет таблицу, динамически подстраивая высоту под n."""
    rows = df.shape[0] if rows_to_show is None else min(rows_to_show, df.shape[0])

    # Настраиваем высоту рисунка в зависимости от n, ограничивая её разумными значениями
    fig_height = min(max(8, n /2), 20)  # Высота от 8 до 20 дюймов

    fig, ax = plt.subplots(figsize=(12, fig_height))
    table = ax.table(cellText=df.values[:rows], colLabels=df.columns, loc='center', bbox=[0, 0, 1, 1])
    table.set_fontsize(10)
    table.auto_set_font_size(False)
    ax.axis('off')
    plt.tight_layout()
    plt.savefig(filename, bbox_inches='tight')
    plt.close(fig)



def read_initial_params(filepath):
    """Читает параметры n и a из файла initial_params.txt. Возвращает None в случае ошибки."""
    try:
        with open(filepath, 'r') as f:
            params = f.readline().strip().split()
            if len(params) < 4:
                print(f"Ошибка: Недостаточно параметров в файле {filepath}. Необходимо хотя бы четыре числа.")
                return None
            try:
                n = int(params[0])
                a = float(params[3])
                return n, a
            except ValueError:
                print(f"Ошибка: Неверный формат параметров в файле {filepath}. Ожидаются числа.")
                return None
    except FileNotFoundError:
        print(f"Ошибка: Файл не найден: {filepath}")
        return None


def main():
    """Главная функция."""
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

    df = process_results(RESULTS_DIR+"results.txt")
    if df is None:
        return

    initial_params = read_initial_params(RESULTS_DIR+"initial_params.txt")
    if initial_params is None:
        return

    n, a = initial_params
    print(f"Прочитано из initial_params.txt: n = {n}, a = {a}")

    plot_results(df,RESULTS_IMAGE_DIR+"graph.png", a)
    print("График сохранен в graph.png")
    create_table(df, n,RESULTS_IMAGE_DIR+"table.png", rows_to_show=110)
    print("Таблица сохранена в table.png")


if __name__ == "__main__":
    main()

