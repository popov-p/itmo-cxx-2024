import pandas as pd
import matplotlib.pyplot as plt

def main():
    dim_files = [(500, "build/dim_500.csv"), (1000, "build/dim_1000.csv")]

    fig, axs = plt.subplots(len(dim_files), 1, figsize=(10, 18))  # 3 строки, 1 столбец

    for i, (dim, file) in enumerate(dim_files):
        data = pd.read_csv(file)

        axs[i].plot(data['Sparsity'], data['CustomMatrixTime'], label=f'CustomMatrix Time (dim={dim})', marker='o',
                    linestyle='-', color='b')

        axs[i].plot(data['Sparsity'], data['StdBasedMatrixTime'], label=f'StdBasedMatrix Time (dim={dim})', marker='o',
                    linestyle='-', color='r')

        axs[i].set_title(f'Search Time Comparison for dim={dim}')
        axs[i].set_xlabel('Sparsity')
        axs[i].set_ylabel('Search Time (seconds)')
        axs[i].legend()
        axs[i].grid(True)

    plt.tight_layout()
    plt.savefig('output.png')
    #plt.show()


if __name__ == "__main__":
    main()
