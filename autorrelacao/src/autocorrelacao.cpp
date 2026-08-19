#include "../include/constantes.h"
#include "../include/autocorrelacao.h"
#include "../include/variaveis_aleatorias.h"
#include "../include/sinal.h"
#include <vector>
#include <cmath>

using namespace constants;

vector<double> gerar_vetor_atrasos(int qt_intervalos){
  vector<double> tempos(qt_intervalos);

  for (int i = 0; i < qt_intervalos; i++) {
      tempos[i] = i * DT;
  }
  return tempos;
}

vector<vector<double>> gerar_matriz_de_sinais(
    int n_funcoes,
    int n_amostras,
    double variancia
  ){
  vector<vector<double>> realizacoes(n_funcoes, vector<double>(n_amostras));

  for (int m=0; m<n_funcoes;m++){
    double fase = generate_va_uniforme(0.0, 2*PI);
    Sinal senoide = criar_sinal(sqrt(2), fase, FC);
    for (int i=0;i<n_amostras;i++){
      double t = i*DT;
      Ruido ruido = criar_ruido(0.0, sqrt(variancia));
      double x = sinal_completo(senoide,ruido,t);
      realizacoes[m][i] = x;
    }
  }
  return realizacoes;
}

vector<double> autocorrelacao(int n_amostras, int n_funcoes,const vector<vector<double>>& realizacoes){
  
  vector<double> autocorrelacoes(n_amostras);
  for(int k=0;k<n_amostras;k++){
    double autocorrelacao = 0;
    for(int m=0;m<n_funcoes;m++){
      double soma = 0;
      for(int i=0;i<n_amostras-k;i++){
        double produto = realizacoes[m][i]*realizacoes[m][i+k];
        soma+=produto;
      }
      autocorrelacao = autocorrelacao + soma/(n_amostras-k);
    }
    autocorrelacoes[k] = autocorrelacao/n_funcoes;
  }
  return autocorrelacoes;
}

pair<vector<double>, vector<double>> gerar_vetores_completos(const vector<double>& tempos, const vector<double>& autocorrelacoes, double tau_min, double tau_max){
  vector<double> vetor_tempo;
  vector<double> vetor_autocorrelacoes;
  int N = autocorrelacoes.size();

  for (int k=N-1; k>=1;k--){
    double tau = -tempos[k];
    
    if(tau>=tau_min && tau<=tau_max){
      vetor_tempo.push_back(tau);
      vetor_autocorrelacoes.push_back(autocorrelacoes[k]);
    }
  }

  if (tau_min<=0.0 && tau_max>=0.0){
      vetor_tempo.push_back(0.0);
      vetor_autocorrelacoes.push_back(autocorrelacoes[0]);
  }

  for (int k = 1; k < N; k++) {
    double tau = tempos[k];
    if(tau>=tau_min && tau<=tau_max){
      vetor_tempo.push_back(tau);
      vetor_autocorrelacoes.push_back(autocorrelacoes[k]);
    }
  }
  return {vetor_tempo, vetor_autocorrelacoes}; 
}
