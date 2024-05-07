#include <stdio.h>

// Função para calcular o fatorial de um número
float factorial(float n) {
  double fat = 1;
  for (; n > 0; n--) {
    fat = fat * n;
  }
  return fat;
}

int main() {
  // Definindo variáveis
  double distancia_total = 0.0;
  double distancia_parcial = 0.0;
  int n = 100;
    
  // Loop para calcular a distância percorrida a cada segundo
  for (int segundo = 1; segundo <= n; segundo++) {
    /* Calculando a distância percorrida no segundo atual usando a série de 
    Taylor da constante de Euler */
    double distancia_segundo = 1.0 / factorial(segundo);

    // Adicionando a distância percorrida no segundo atual à distância total
    distancia_parcial += distancia_segundo;

    // Imprimindo a distância percorrida no segundo atual e a distância parcial
    printf("Segundo %d: Andou %.8f|Distância parcial: %.50f metros\n", segundo, distancia_segundo, distancia_parcial); 
  }
    
    // Imprime a distância total percorrida
    printf("\nDistância total: %.8f metros", distancia_parcial);

  return 0;
}
