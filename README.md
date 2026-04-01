# 📡 Telecom & Electronics Lab: Práticas em C++

Repositório dedicado à implementação de modelos matemáticos e físicos estudados em Engenharia de Telecomunicações e Eletrônica. O foco é transformar a teoria de sinais e componentes em algoritmos funcionais.

---

## 🚀 Projetos Atuais

### 1. ⚡ Cálculo de Corrente no Diodo
Este projeto implementa a **Equação de Shockley** para modelar o comportamento de um diodo de junção PN. É o ponto de partida para entender como a não-linearidade dos semicondutores é fundamental para circuitos de telecomunicação.

* **Conceitos Aplicados:** * Corrente de saturação inversa ($I_S$).
    * Potencial térmico ($V_T$) e influência da temperatura.
    * Fator de idealidade do diodo.
* **Fórmula Base:**
    $$I = I_S \left( e^{\frac{V_D}{n V_T}} - 1 \right)$$

### 2. 📻 Modulação em Amplitude (AM)
Simulação do processo de modulação AM-DSB-FC (Double Sideband Full Carrier). O projeto gera as amostras de um sinal modulado para análise de índice de modulação e faixas de frequência.

* **Conceitos Aplicados:**
    * Frequência da Portadora ($f_c$) vs. Frequência da Mensagem ($f_m$).
    * Índice de modulação ($m$) e análise de sobremodulação.
    * Espectro de frequências e potência de sinal.
* **Fórmula Base:**
    $$s(t) = [A_c + m(t)] \cdot \cos(2\pi f_c t)$$

---

## 🛠 Como Compilar e Rodar

Certifique-se de ter o `g++` (GCC) instalado.

1.  **Clonar o repositório:**
    ```bash
    git clone [https://github.com/seu-usuario/telecom-cpp.git](https://github.com/seu-usuario/telecom-cpp.git)
    ```
2.  **Compilar um projeto:**
    ```bash
    g++ -O3 projeto_am/main.cpp -o sim_am
    ```
3.  **Executar:**
    ```bash
    ./sim_am
    ```

---

## 📊 Visualização dos Resultados

Os programas geram arquivos `.csv` com as amostras dos sinais. Para visualizar os gráficos, você pode usar o **Gnuplot** ou este snippet rápido em **Python**:

```python
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('resultado.csv')
plt.plot(df['tempo'], df['sinal'])
plt.show()
