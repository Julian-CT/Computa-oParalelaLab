## 1 - 

Tempo de execução em 1 processador:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/6dc3a7fe-4544-4881-8d17-94e58c418a65)

Tempo de execução em 2 processadores:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/573376ab-f63e-4731-a121-3e122caa4381)

Tempo de execução em 4 processadores:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/2d6b0d66-0c9d-40f2-8f50-f38a946d7325)

Tempo de execução em 6 processadores:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/fd8cde70-eb89-4ac2-8e4f-15625766d490)


Tempo de execução em 8 processadores:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/19ea4429-b634-4447-8208-e85f2256b09d)

## 2-

Cálculo do speedup em 2 processadores:

S = T(1)/T(N) --> S = 0,69/0,54 ≃ 1,28

Cálculo do speedup em 4 processadores:

S = T(1)/T(N) --> S = 0,69/0,42 ≃ 1,64

Cálculo do speedup em 6 processadores:

S = T(1)/T(N) --> S = 0,69/0,23 = 3

Cálculo do speedup em 8 processadores:

S = T(1)/T(N) --> S = 0,69/0,21 ≃ 3,29

Gráfico dos speedups

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/bb017c8d-2e2e-41fd-a076-51c6eab7ae36)


## 3-

Ao introduzir a diretiva critical na solução, estamos garantindo que apenas uma thread execute a seção crítica do código por vez. Isso é útil quando várias threads podem tentar acessar ou modificar uma região crítica de dados simultaneamente, o que poderia resultar em condições de corrida. Com essa modificação, a seção crítica onde a variável sum é atualizada é protegida pela diretiva critical, garantindo que apenas uma thread execute essa parte do código por vez. Isso evita condições de corrida e torna o código seguro para execução paralela.

Tempo de execução em 1 processador com a derivativa critical:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/2e6e182d-90df-4cab-a02f-c6248f5ffbdd)

Tempo de execução em 2 processadores com a derivativa critical:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/f1826069-b3e3-4bb5-ae4d-c1bdfb0a1a04)

Tempo de execução em 4 processadores com a derivativa critical:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/e45b5939-95b0-4d9a-bdb4-f7d36275e9df)

Tempo de execução em 6 processadores com a derivativa critical:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/5f516ccb-6185-4d39-973a-1b2f21dcebf5)

Tempo de execução em 8 processadores com a derivativa critical:

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/110931de-e26c-486d-9522-610b18715386)

Cálculo do speedup em 2 processadores:

S = T(1)/T(N) --> S = 0,73/0,56 ≃ 1,30

Cálculo do speedup em 4 processadores:

S = T(1)/T(N) --> S = 0,73/0,31 ≃ 2,35

Cálculo do speedup em 6 processadores:

S = T(1)/T(N) --> S = 0,73/0,24 = 3,04

Cálculo do speedup em 8 processadores:

S = T(1)/T(N) --> S = 0,73/0,18 ≃ 4,05

## Especificações do Processador

Intel i3 1215u

![image](https://github.com/Julian-CT/Computa-oParalelaLab/assets/144359181/2f54d488-f131-4ab4-a8d1-ccf29f31fea6)



