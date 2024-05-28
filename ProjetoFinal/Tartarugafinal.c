#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <omp.h> // Inclusão da biblioteca OpenMP para funcionalidades de paralelização

#define NUM_THREADS 8 // Define o número de threads que serão usadas
#define NUM_TERMS 100 // Define o número de termos da série de Taylor a serem calculados

double e_total = 0.0; // Variável global para armazenar o valor total de e

// Função para calcular o fatorial de um número
double factorial(int n) {
    if (n == 0 || n == 1) { // Se n for 0 ou 1, retorna 1, pois 0! e 1! são ambos 1
        return 1.0;
    }
    double fat = 1.0; // Inicializa a variável fat para 1
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

    double e_parcial = 0.0; // Variável para armazenar a soma parcial calculada por esta thread
    for (int termo = inicio; termo < fim; termo++) { // Loop através dos termos atribuídos a esta thread
        e_parcial += 1.0 / factorial(termo); // Adiciona 1/factorial(termo) à soma parcial
    }

    #pragma omp critical // Seção crítica do OpenMP para garantir exclusão mútua
    {
        e_total += e_parcial; // Adiciona a soma parcial ao total global
    }

    pthread_exit(NULL); // Termina a thread
}

int main() {
    pthread_t threads[NUM_THREADS]; // Array para armazenar os identificadores das threads

    omp_set_num_threads(NUM_THREADS); // Define o número de threads para OpenMP

    for (long t = 0; t < NUM_THREADS; t++) { // Cria as threads
        pthread_create(&threads[t], NULL, calcularE, (void *)t); // Cria uma nova thread que executa a função calcularE
    }

    for (int i = 0; i < NUM_THREADS; i++) { // Espera todas as threads terminarem
        pthread_join(threads[i], NULL); // Bloqueia até que a thread especificada termine
    }

    e_total += 0.0;

    printf("A tartaruga andou: %.50f\n", e_total); // Imprime o valor total calculado de e com alta precisão

    pthread_exit(NULL); // Termina o programa principal
}
