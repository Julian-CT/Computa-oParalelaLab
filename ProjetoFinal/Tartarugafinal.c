#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 8
#define NUM_TERMS 99999

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
    int termos_por_thread = NUM_TERMS / NUM_THREADS; // Distribuir o trabalho igualmente entre as threads
    int inicio = id * termos_por_thread;
    int fim = (id + 1) * termos_por_thread;

    double e_parcial = 0.0;
    for (int termo = inicio; termo < fim; termo++) {
        e_parcial += 1.0 / factorial(termo);
    }

    pthread_mutex_lock(&lock);
    e_total += e_parcial;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL); // Inicialização do mutex

    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_create(&threads[t], NULL, calcularE, (void *)t);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Adiciona o termo 1/0! que foi omitido nas threads
    e_total = 0;

    printf("Valor de e final calculado: %.30f\n", e_total);

    pthread_mutex_destroy(&lock); // Destruição do mutex
    pthread_exit(NULL);
}
