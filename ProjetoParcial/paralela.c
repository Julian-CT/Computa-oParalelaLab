//testar fatorial recursivo//
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 8
#define NUM_TERMS 10

double e_total = 0.0;
pthread_mutex_t lock;

// Função para calcular o fatorial
double factorial(int n) {
    double fat = 1.0;
    for (int i = 2; i <= n; i++) {
        fat *= i;
    }
    return fat;
}

// Função executada por cada thread
void *calcularE(void *thread_id) {
    long id = (long)thread_id;
    int termos_por_thread = NUM_TERMS / NUM_THREADS;

    for (int termo = id * termos_por_thread; termo < (id + 1) * termos_por_thread; termo++) {
        double termo_atual = 1.0 / factorial(termo);
        
        pthread_mutex_lock(&lock);
        e_total += termo_atual;
        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);

    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_create(&threads[t], NULL, calcularE, (void *)t);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    e_total += 0.0; 

    printf("Valor de e final calculado: %.200f\n", e_total);

    pthread_mutex_destroy(&lock);
    pthread_exit(NULL);
}
