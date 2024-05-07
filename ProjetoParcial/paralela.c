#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Número de threads a serem usadas
#define NUM_THREADS 8

double e_total = 0.0;
pthread_mutex_t lock; // Mutex para garantir exclusão mútua ao acessar a variável compartilhada

// Função para calcular o fatorial
double factorial(int n) {
    double fat = 1;
    for (; n > 0; n--) {
        fat *= n;
    }
    return fat;
}

// Função executada por cada thread
void *calcularE(void *thread_id) {
    long id = (long)thread_id;
    int termos_por_thread = 100 / NUM_THREADS; // Distribuir o trabalho igualmente entre as threads

    for (int termo = id * termos_por_thread; termo < (id + 1) * termos_por_thread; termo++) {
        double termo_atual = 1.0 / factorial(termo);
        
        // Trava a variável e_total para garantir exclusão mútua
        pthread_mutex_lock(&lock);
        e_total += termo_atual;
        pthread_mutex_unlock(&lock); // Destrava a variável e_total
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL); // Inicialização do mutex

    clock_t start, end;
    double elapsed_time;

    start = clock(); // Início da contagem do tempo

    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_create(&threads[t], NULL, calcularE, (void *)t);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    end = clock(); // Fim da contagem do tempo

    elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Valor de e final calculado: %.10f\n", e_total);
    printf("Tempo total de execução: %.6f segundos\n", elapsed_time);

    pthread_mutex_destroy(&lock); // Destruição do mutex
    pthread_exit(NULL);
}
