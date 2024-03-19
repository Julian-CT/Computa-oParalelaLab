#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define M 1000
#define N 1000
#define NUM_THREADS 8

double A[M][N];
double x[N];
double y[M];

typedef struct {
    int start_row;
    int end_row;
} ThreadData;

void generate_random_matrix(double A[M][N], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A[i][j] = (double) rand() / RAND_MAX;  // Valor aleatório entre 0 e 1
        }
    }
}

void generate_random_vector(double x[N], int size) {
    for (int i = 0; i < size; i++) {
        x[i] = (double) rand() / RAND_MAX;  // Valor aleatório entre 0 e 1
    }
}

void *calculate_partial_sum(void *thread_arg) {
    ThreadData *data = (ThreadData *) thread_arg;
    int start_row = data->start_row;
    int end_row = data->end_row;

    for (int i = start_row; i < end_row; i++) {
        y[i] = 0.0;
        for (int j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    pthread_exit(NULL);
}

double calculate_execution_time(struct timespec start_time, struct timespec end_time) {
    return (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    srand((unsigned int) time(NULL));

    // Gerar matriz e vetor aleatórios
    generate_random_matrix(A, M, N);
    generate_random_vector(x, N);

    // Capturar tempo de início
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Dividir o trabalho entre as threads
    int chunk_size = M / NUM_THREADS;
    for (int t = 0; t < NUM_THREADS; t++) {
        thread_data[t].start_row = t * chunk_size;
        thread_data[t].end_row = (t + 1) * chunk_size;
        if (t == NUM_THREADS - 1) {
            thread_data[t].end_row = M;  // Lidar com o caso onde M não é divisível por NUM_THREADS
        }
        pthread_create(&threads[t], NULL, calculate_partial_sum, (void *)&thread_data[t]);
    }

    // Aguardar término das threads
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // Capturar tempo de término
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    // Imprimir vetor resultante y
    printf("Vetor resultante y:\n");
    for (int i = 0; i < M; i++) {
        printf("%.2f ", y[i]);
    }
    printf("\n");

    // Calcular e imprimir o tempo de execução
    printf("Tempo de execução: %.6f segundos\n", calculate_execution_time(start_time, end_time));

    return 0;
}
