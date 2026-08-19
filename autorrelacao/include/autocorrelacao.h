#pragma once
#include <vector>
using namespace std;

vector<double> gerar_vetor_atrasos(int qt_intervalos);

vector<vector<double>> gerar_matriz_de_sinais(int n_funcoes, int n_amostras, double variancia);

vector<double> autocorrelacao(int n_amostras, int n_funcoes, const vector<vector<double>>& realizacoes);

pair<vector<double>, vector<double>> gerar_vetores_completos(const vector<double>& tempos, const vector<double>& autocorrelacoes, double tau_min, double tau_max);
