# Simulador de Modulação AM

Projeto didático em C++ que simula a modulação em amplitude (AM) e gera um gráfico do sinal modulado ao longo do tempo.

## Estrutura do projeto

```
projeto/
├── Makefile
├── README.md
├── main.cpp
├── include/
│   ├── signal.h
│   ├── export.h
│   └── matplotlibcpp.h
└── src/
    ├── signal.cpp
    └── export.cpp
```

## Dependências

- g++ com suporte a C++17
- Python 3 com matplotlib e numpy

```bash
sudo apt install python3-matplotlib python3-numpy python3-dev
```

## Como compilar

```bash
make
```

## Como executar

```bash
./simulador
```

O programa gera o arquivo `resultados.csv` com os valores calculados e exibe o gráfico do sinal AM.

## Parâmetros do sinal

Definidos em `main.cpp`:

| Parâmetro | Valor | Descrição |
|---|---|---|
| `frequencia_C` | 10000 Hz | Frequência da portadora |
| `frequencia_M` | 500 Hz | Frequência da mensagem |
| `amplitude_C` | 1.0 | Amplitude da portadora |
| `amplitude_M` | 0.5 | Amplitude da mensagem |

O índice de modulação resultante é `Am / Ac = 0.5`.

## Conceitos envolvidos

- Modulação em amplitude (AM)
- Critério de Nyquist e taxa de amostragem
- Integração numérica
- Exportação de dados em CSV
- Visualização com matplotlib

## Limpeza

```bash
make clean
```
