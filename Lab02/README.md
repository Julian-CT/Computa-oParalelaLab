# Primeira Parte

- Código em C para realizar multiplicação de matrizes usando pthreads

- Print do código rodando na AWS clodshell 

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/7362a338-a3bb-4a36-b44e-bda9afdb53e5)

# Segunda Parte

## Lab02b (Mal otimizado)
### Tempo de execução serial/paralelo:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/35000046-0cf6-4ab7-a268-fe0c93ca0747)

### Gráfico dos tempo de execução
![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/5aa85f87-6c5a-4130-bc93-20ae10e78124)


### Cálculo do speedup dos processadores:

Sp = T1/Tp

  2 processadores -> Sp = 0,0047/0,0049 = 0,96

  4 processadores -> Sp = 0,0047/0,0056 = 0,84

  6 processadores -> Sp = 0,0047/0,0060 = 0,78

  8 processadores -> Sp = 0,0047/0,0070 = 0,67

### Gráfico SpeedUps
![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144508430/68831641-7177-435d-a018-19651ced81b4)


### Otimização
- Para otimizar o tempo e garantir o paralelismo, é preciso garantir que as threads estejam distribuindo o trabalho de maneira equitativa, evitando que algumas fiquem ociosas enquanto outras estão ocupadas.
- Nesta versão, dividimos o trabalho entre várias threads, onde cada thread é responsável por calcular uma parte das linhas da matriz A. Cada thread recebe uma estrutura ThreadData que contém o intervalo de linhas que ela deve calcular. Depois de calcular as somas parciais, as threads terminam e o programa principal espera que todas elas terminem antes de imprimir o vetor resultante y.

## Lab02botm (Otimizado)
### Tempo de execução:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/26b19844-f899-466b-89b2-c33d67c02188)

### Cálculo SpeedUp:

Speedup = T1/Tn

2 processadores -> Sp = 0,005688 / 0,003222 = 1,76

4 processadores -> Sp = 0,005688 / 0,002340 = 2,43

6 processadores -> Sp = 0,00588 / 0,001883 = 3,02

8 processadores -> Sp = 0,005688 / 0,000977 = 5,82

### Gráfico SpeedUp:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144508430/828274e7-458d-4b1b-a588-e915e7dfa9ec)


### Especificações do processador

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/0cd89ae8-5005-4c0d-879f-31496e88e28f)



