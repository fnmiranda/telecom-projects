import numpy as np

# Configurações do problema
num_sinais = 100
num_amostras = 30000
A = 1.0  # Amplitude da senoide
f = 50  # Frequência de 50 Hz
fs = 1000  # Frequência de amostragem de 1 kHz

# Eixo do tempo (30.000 pontos)
t = np.arange(num_amostras) / fs

# Gerar 100 fases aleatórias uniformes entre 0 e 2*pi
np.random.seed(42)  # Mantém os resultados reprodutíveis
fases = np.random.uniform(0, 2 * np.pi, num_sinais)

# Criar a matriz com as 100 senoides (linhas) e 30.000 amostras (colunas)
sinais = np.zeros((num_sinais, num_amostras))
for i in range(num_sinais):
    sinais[i, :] = A * np.sin(2 * np.pi * f * t + fases[i])

# --- COMPROVAÇÃO DA ERGODICIDADE ---

# 1. Estatísticas de UMA ÚNICA SENOIDE ao longo de todo o tempo (Média Temporal)
media_temporal = np.mean(sinais[0, :])
potencia_temporal = np.mean(sinais[0, :] ** 2)

# 2. Estatísticas de TODOS OS SINAIS em um único instante fixo (Média do Conjunto / Espacial)
instante_fixo = 500
media_espacial = np.mean(sinais[:, instante_fixo])
potencia_espacial = np.mean(sinais[:, instante_fixo] ** 2)

print(f"Média Temporal (1 sinal / 30k amostras): {media_temporal:.4f}")
print(f"Média Espacial (100 sinais / instante {instante_fixo}): {media_espacial:.4f}\n")
print(f"Potência Temporal (1 sinal / 30k amostras): {potencia_temporal:.4f}")
print(
    f"Potência Espacial (100 sinais / instante {instante_fixo}): {
        potencia_espacial:.4f}"
)
