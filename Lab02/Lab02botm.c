#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Número de linhas e colunas da matriz
#define m 100
#define n 50

// Função para contar o tempo de execução
double get_execution_time(double start_time) {
    return omp_get_wtime() - start_time;
}

// Função principal
int main() {
    // Declaração da matriz A, vetor x e vetor resultante y
    double A[m][n], x[n], y[m];
    int i, j;

    // Inicialização da matriz A
    printf("Matriz A:\n");
    double start_time = omp_get_wtime(); // Marca o início da inicialização da matriz A
    #pragma omp parallel for private(j)
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = i + j + 1;
            printf("%.2f ", A[i][j]);
        }
        printf("\n");
    }
    double initialization_time = get_execution_time(start_time); // Calcula o tempo de execução da inicialização

    // Inicialização do vetor x
    printf("\nVetor x:\n");
    start_time = omp_get_wtime(); // Marca o início da inicialização do vetor x
    #pragma omp parallel for
    for (j = 0; j < n; j++) {
        x[j] = j + 1;
        printf("%.2f\n", x[j]);
    }
    double vector_initialization_time = get_execution_time(start_time); // Calcula o tempo de execução da inicialização do vetor x

    // Variável para armazenar o número de processadores a serem utilizados
    int num_processors;

    // Cálculo do produto matriz-vetor
    printf("\nCalculando o produto matriz-vetor...\n");
    printf("Quantos processadores você deseja utilizar (1, 2, 4, 6 ou 8)? ");
    scanf("%d", &num_processors); // Leitura do número de processadores a serem utilizados

    start_time = omp_get_wtime(); // Marca o início do cálculo do produto matriz-vetor
    omp_set_num_threads(num_processors); // Define o número de threads a serem utilizadas
    #pragma omp parallel for private(j)
    for (i = 0; i < m; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    double matrix_vector_product_time = get_execution_time(start_time); // Calcula o tempo de execução do cálculo do produto matriz-vetor

    // Impressão do vetor resultante y
    printf("\nVetor resultante y:\n");
    for (i = 0; i < m; i++) {
        printf("%.2f ", y[i]);
    }
    printf("\n");

    // Impressão do tempo de execução
    printf("\nTempo de execução da inicialização da matriz A: %.6f segundos\n", initialization_time);
    printf("Tempo de execução da inicialização do vetor x: %.6f segundos\n", vector_initialization_time);
    printf("Tempo de execução do cálculo do produto matriz-vetor: %.6f segundos\n", matrix_vector_product_time);

    return 0;
}
