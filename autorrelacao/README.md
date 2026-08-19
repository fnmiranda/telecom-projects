
# Simulador de Autocorrelação de Processos Aleatórios

Projeto em C++ para geração de funções amostrais de um processo aleatório composto por uma senoide com fase aleatória e ruído gaussiano aditivo, além do cálculo e visualização de sua função de autocorrelação.

O projeto foi desenvolvido a partir do trabalho da disciplina **Comunicações Analógicas e Digitais II — IME**.

---

## Processo Aleatório

O processo analisado é:

[
X(t)=A\cos(2\pi f_c t+\Theta)+W(t)
]

onde:

* (A=\sqrt{2});
* (f_c=8\times10^{-3}) Hz;
* (\Theta\sim U(0,2\pi));
* (W(t)) é uma variável aleatória gaussiana de média nula;
* a variância de (W(t)) depende da SNR utilizada.

São considerados os valores:

```text
SNR = 15 dB
SNR = 5 dB
SNR = 0 dB
```

Cada função amostral possui:

```text
N = 30000 amostras
dt = 0.01 s
```

e são geradas:

```text
100 funções amostrais
```

para o cálculo da autocorrelação.

---

## Estrutura do Projeto

```text
projeto/
├── include/
│   ├── constants.h
│   ├── variaveis_aleatorias.h
│   ├── sinal.h
│   ├── autocorrelacao.h
│   └── graficos.h
│
├── src/
│   ├── main.cpp
│   ├── variaveis_aleatorias.cpp
│   ├── sinal.cpp
│   ├── autocorrelacao.cpp
│   └── graficos.cpp
│
├── third_party/
│   └── matplotlibcpp.h
│
├── build/
│
├── Makefile
└── README.md
```

### `include/`

Contém as declarações das funções, estruturas e constantes utilizadas no projeto.
Contém bibliotecas externas utilizadas pelo projeto, como `matplotlibcpp`.

### `src/`

Contém as implementações dos algoritmos.


### `build/`

Diretório utilizado para armazenar os arquivos objeto (`.o`) gerados durante a compilação.

---

## Geração das Funções Amostrais

Cada realização utiliza uma fase aleatória:

[
\Theta_m\sim U(0,2\pi)
]

que permanece constante durante toda a realização.

Para cada instante:

[
t_i=i\Delta t
]

é gerado um novo valor de ruído gaussiano:

[
W_m[i]\sim\mathcal N(0,\sigma_W^2)
]

e então:

[
X_m[i]
======

\sqrt2\cos(2\pi f_ct_i+\Theta_m)
+
W_m[i].
]

As realizações são armazenadas em:

```cpp
std::vector<std::vector<double>> realizacoes;
```

de forma que:

```cpp
realizacoes[m][i]
```

representa a amostra `i` da realização `m`.

---

## SNR e Variância do Ruído

A potência da senoide é:

[
P_s=\frac{A^2}{2}=1.
]

A relação sinal-ruído é:

[
SNR_{dB}
========

10\log_{10}
\left(
\frac{P_s}{P_w}
\right).
]

Portanto:

[
P_w
===

10^{-SNR_{dB}/10}.
]

Como o ruído possui média nula:

[
\sigma_W^2=P_w.
]

Assim:

[
\boxed{
\sigma_W^2=10^{-SNR_{dB}/10}
}
]

---

## Autocorrelação

A autocorrelação estimada é calculada por:

[
\hat R_X[k]
===========

\frac{1}{M}
\sum_{m=0}^{M-1}
\left[
\frac{1}{N-k}
\sum_{i=0}^{N-k-1}
X_m[i]X_m[i+k]
\right]
]

onde:

* (M=100) é o número de funções amostrais;
* (N=30000) é o número de amostras;
* (k) representa o atraso em número de amostras.

O atraso físico correspondente é:

[
\tau=k\Delta t.
]

Para processos reais, a autocorrelação possui a propriedade:

[
R_X(-\tau)=R_X(\tau).
]

Por isso, somente os atrasos positivos precisam ser calculados. A parte negativa pode ser obtida por espelhamento.

---

## Gráficos

Para cada valor de SNR são gerados:

1. primeira função amostral;
2. segunda função amostral;
3. terceira função amostral;
4. função de autocorrelação.

Os gráficos são gerados através da biblioteca:

```text
matplotlib-cpp
```

que utiliza o Matplotlib do Python internamente.

---

## Dependências

O projeto utiliza:

```text
C++17 ou superior
G++
Python 3
Python development headers
Matplotlib
matplotlib-cpp
```

Em Ubuntu/WSL:

```bash
sudo apt update
sudo apt install build-essential python3-dev python3-matplotlib
```

Verifique as flags do Python:

```bash
python3-config --includes
python3-config --ldflags --embed
```

---

## Compilação

Utilizando o `Makefile`:

```bash
make
```


Para remover os arquivos compilados:

```bash
make clean
```

Para recompilar completamente:

```bash
make clean
make
```

---


## Organização do Código

O projeto segue a separação de responsabilidades:

```text
main.cpp
    ↓
coordena a execução do programa

variaveis_aleatorias.cpp
    ↓
gera variáveis uniformes e gaussianas

sinal.cpp
    ↓
gera senoide e funções amostrais

autocorrelacao.cpp
    ↓
calcula a autocorrelação

graficos.cpp
    ↓
gera os gráficos
```

A `main()` deve apenas coordenar essas etapas, evitando concentrar os algoritmos nela.

---

## Objetivo

O projeto tem como objetivo estudar numericamente:

* geração de processos aleatórios;
* variáveis aleatórias uniformes;
* variáveis aleatórias gaussianas;
* ruído aditivo;
* relação sinal-ruído;
* funções amostrais;
* autocorrelação;
* médias temporais e de ensemble;
* propriedades de estacionariedade e ergodicidade.
