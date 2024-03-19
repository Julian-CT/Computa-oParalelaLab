#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Adicionado para medir o tempo de execução

// Definindo constantes
#define MAX_THREADS 8

// Número de linhas e colunas da matriz
int m = 100;
int n = 50;

// Número de threads a serem usadas
int thread_count = 8; // Altere este valor para 2, 4, 6 ou 8

// Declarando a matriz, vetor e vetor resultante
double A[100][50];
double x[50];
double *y;

// Função que cada thread vai executar
void *Pth_mat_vect(void *rank) {
  long my_rank = (long)rank;
  int i, j;
  int local_m = m / thread_count;
  int my_first_row = my_rank * local_m;
  int my_last_row =
      (my_rank + 1 == thread_count) ? (m - 1) : (my_first_row + local_m - 1);

  // Para cada linha que essa thread é responsável
  for (i = my_first_row; i <= my_last_row; i++) {
    // Inicializa o elemento do vetor resultante como zero
    y[i] = 0.0;
    // Calcula o produto interno entre a linha da matriz e o vetor
    for (j = 0; j < n; j++) {
      y[i] += A[i][j] * x[j];
    }
  }
  return NULL;
}

// Função para medir o tempo de execução
double get_execution_time(clock_t start, clock_t end) {
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

// Função principal
int main() {
  long thread;
  pthread_t *thread_handles;
  clock_t start, end; // Variáveis para medir o tempo de execução

  // Inicialização da matriz A
  printf("Matriz A:\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      A[i][j] = i + j + 1;
      printf("%.2f ", A[i][j]);
    }
    printf("\n");
  }

  // Inicialização do vetor x
  printf("\nVetor x:\n");
  for (int j = 0; j < n; j++) {
    x[j] = j + 1;
    printf("%.2f\n", x[j]);
  }
  printf("\n");

  // Alocação de memória para o vetor resultante y
  y = malloc(m * sizeof(double));

  // Alocação de memória para os identificadores das threads
  thread_handles = malloc(thread_count * sizeof(pthread_t));

  // Início da medição do tempo de execução
  start = clock();

  // Criação das threads
  for (thread = 0; thread < thread_count; thread++) {
    pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *)thread);
  }

  // Aguarda o término das threads
  for (thread = 0; thread < thread_count; thread++) {
    pthread_join(thread_handles[thread], NULL);
  }

  // Fim da medição do tempo de execução
  end = clock();

  // Imprime o vetor resultante y
  printf("Vetor resultante y:\n");
  for (int i = 0; i < m; i++) {
    printf("%.2f ", y[i]);
  }
  printf("\n");

  // Imprime o tempo de execução
  printf("Tempo de execução: %.4f segundos\n", get_execution_time(start, end));

  // Libera a memória
  free(thread_handles);
  free(y);

  return 0;
}
