#include <stdio.h>
#include <math.h>
#include <omp.h>

#define NUM_THREADS 8
#define NUM_SUBINTERVALS 1000000
#define LOWER_BOUND 0.0
#define UPPER_BOUND M_PI

double f(double x) {
    return sin(x);
}

int main() {
    double interval_width = (UPPER_BOUND - LOWER_BOUND) / NUM_SUBINTERVALS;
    double sum = 0.0;
    
    #pragma omp parallel for num_threads(NUM_THREADS) reduction(+:sum)
    for (int i = 0; i < NUM_SUBINTERVALS; ++i) {
        double x_left = LOWER_BOUND + i * interval_width;
        double x_right = x_left + interval_width;
        double height = (f(x_left) + f(x_right)) / 2.0;
        double area = height * interval_width;
        sum += area;
    }

    printf("Aproximação da área sob a curva: %f\n", sum);
    
    return 0;
}
