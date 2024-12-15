import pandas as pd
import matplotlib.pyplot as plt


def main():
    dim_files = [(500, "build/dim_500.csv"), (1000, "build/dim_1000.csv")]

    # Создаем фигуру с тремя подграфиками
    fig, axs = plt.subplots(len(dim_files), 1, figsize=(10, 18))  # 3 строки, 1 столбец

    for i, (dim, file) in enumerate(dim_files):
        data = pd.read_csv(file)

        # Для каждого графика рисуем данные только один раз на соответствующей оси axs[i]
        axs[i].plot(data['Sparsity'], data['CustomMatrixTime'], label=f'CustomMatrix Time (dim={dim})', marker='o',
                    linestyle='-', color='b')

        axs[i].plot(data['Sparsity'], data['StdBasedMatrixTime'], label=f'StdBasedMatrix Time (dim={dim})', marker='o',
                    linestyle='-', color='r')

        axs[i].set_title(f'Search Time Comparison for dim={dim}')
        axs[i].set_xlabel('Sparsity')
        axs[i].set_ylabel('Search Time (seconds)')
        axs[i].legend()  # Легенда
        axs[i].grid(True)  # Сетка

    plt.tight_layout()  # Подгонка расположения графиков
    plt.savefig('output.png')  # Сохранение изображения
    plt.show()  # Отображение графиков


if __name__ == "__main__":
    main()
