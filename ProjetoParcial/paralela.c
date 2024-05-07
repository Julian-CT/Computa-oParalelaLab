#include <stdio.h>
#include <pthread.h>

// Número de threads a serem usadas
#define NUM_THREADS 8
#define TIME_TARTARUGA 12

double distancia_total = 0.0;
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
void *calcularDistancia(void *thread_id) {
    long id = (long)thread_id;
    int segundos_por_thread = TIME_TARTARUGA / NUM_THREADS; // Distribuir o trabalho igualmente entre as threads

    for (int segundo = id * segundos_por_thread + 1; segundo <= (id + 1) * segundos_por_thread; segundo++) {
        double distancia_segundo = 1.0 / factorial(segundo);

        // Trava a variavel distancia_total para garantir exclusão mútua
        pthread_mutex_lock(&lock);
        distancia_total += distancia_segundo;
        pthread_mutex_unlock(&lock); // Destrava a variavel distancia_total

        printf("Thread %ld - Segundo %d: Andou %.8f | Distância parcial: %.8f metros\n", id, segundo, distancia_segundo, distancia_total);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL); // Inicialização do mutex

    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_create(&threads[t], NULL, calcularDistancia, (void *)t);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Distância total: %.8f metros\n", distancia_total);

    pthread_mutex_destroy(&lock); // Destruição do mutex
    pthread_exit(NULL);
}
