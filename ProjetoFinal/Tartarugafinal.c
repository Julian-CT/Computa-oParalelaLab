#include <stdio.h> // Proporciona funções de entrada e saída, como printf.
#include <pthread.h> // Inclui as funções da biblioteca POSIX para programação com threads.
#include <stdlib.h> // Inclui funções utilitárias, como malloc, free, e atoi.
#include <omp.h> // Inclusão da biblioteca OpenMP para funcionalidades de paralelização

#define NUM_THREADS 4 // Define o número de threads que serão usadas
#define NUM_TERMS 100 // Define o número de termos da série de Taylor a serem calculados

long double e_total = 0.0; // Variável global para armazenar o valor total de e
pthread_mutex_t lock; // Mutex para garantir exclusão mútua ao acessar a variável compartilhada

// Função para calcular o fatorial de um número
long double factorial(int n) {
    if (n == 0 || n == 1) { // Se n for 0 ou 1, retorna 1, pois 0! e 1! são ambos 1
        return 1.0;
    }
    long double fat = 1.0; // Inicializa a variável fat para 1
    for (int i = 2; i <= n; i++) { // Loop de 2 até n
        fat *= i; // Multiplica fat pelo valor atual de i
    }
    return fat; // Retorna o fatorial calculado
}

// Função executada por cada thread
void *calcularE(void *thread_id) {
    long id = (long)thread_id; // Converte o id da thread para um tipo long
    int termos_por_thread = NUM_TERMS / NUM_THREADS; // Calcula quantos termos cada thread deve processar
    int inicio = id * termos_por_thread; // Calcula o termo inicial para esta thread
    int fim = (id + 1) * termos_por_thread; // Calcula o termo final para esta thread

    for (int termo = inicio; termo < fim; termo++) { // Loop através dos termos atribuídos a esta thread
        long double termo_valor = 1.0 / factorial(termo); // Calcula 1/factorial(termo)

        pthread_mutex_lock(&lock); // Início da seção crítica
        e_total += termo_valor; // Adiciona o valor do termo ao total global
        pthread_mutex_unlock(&lock); // Fim da seção crítica
    }

    pthread_exit(NULL); // Termina a thread
}

int main() {
    pthread_t threads[NUM_THREADS]; // Array para armazenar os identificadores das threads
    pthread_mutex_init(&lock, NULL); // Inicialização do mutex

    omp_set_num_threads(NUM_THREADS); // Define o número de threads para OpenMP

    for (long t = 0; t < NUM_THREADS; t++) { // Cria as threads
        pthread_create(&threads[t], NULL, calcularE, (void *)t); // Cria uma nova thread que executa a função calcularE
    }

    for (int i = 0; i < NUM_THREADS; i++) { // Espera todas as threads terminarem
        pthread_join(threads[i], NULL); // Bloqueia até que a thread especificada termine
    }

    e_total += 0.0; // Inicializa a série de Taylor

    printf("A tartaruga andou: %.100Lf\n", e_total); // Imprime o valor total calculado de e com alta precisão
    printf("No segundo: %d\n", NUM_TERMS);

    pthread_mutex_destroy(&lock); // Destruição do mutex

    pthread_exit(NULL); // Termina o programa principal
}
