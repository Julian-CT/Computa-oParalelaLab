#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define M 1000
#define N 1000
#define THREAD_COUNT 4

double A[M][N];
double x[N];
double y[M];
pthread_mutex_t mutex;

void *Pth_mat_vect(void *rank) {
    long my_rank = (long) rank;
    int local_m = M / THREAD_COUNT;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m;

    for (int i = my_first_row; i < my_last_row; i++) {
        y[i] = 0.0;
        for (int j = 0; j < N; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    return NULL;
}

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

double calculate_execution_time(clock_t start_time, clock_t end_time) {
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

int main() {
    pthread_t thread_handles[THREAD_COUNT];
    long thread;
    clock_t start_time, end_time;
    srand((unsigned int) time(NULL));
    pthread_mutex_init(&mutex, NULL); // Inicialização do mutex

    // Gerar matriz e vetor aleatórios
    generate_random_matrix(A, M, N);
    generate_random_vector(x, N);

    // Marcar o início do cálculo
    start_time = clock();

    // Criar threads
    for (thread = 0; thread < THREAD_COUNT; thread++) {
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *) thread);
    }

    // Aguardar término das threads
    for (thread = 0; thread < THREAD_COUNT; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    // Marcar o fim do cálculo
    end_time = clock();

    // Destruir o mutex
    pthread_mutex_destroy(&mutex);

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
