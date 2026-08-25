#include "../include/constantes.h"
#include "../include/autocorrelacao.h"
#include "../include/variaveis_aleatorias.h"
#include "../include/sinal.h"
#include <vector>
#include <cmath>
#include <complex>

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

int bitwise(int i, int n_bits){
  int j =0;
  for (int k=0;k<n_bits;k++){
    j = (j<<1)|(i&1);
    i>>=1;
  }
  return j;
}



complex<double> j(0.0, 1.0);

complex<double> w_k(int k, int n){
  complex<double> expoente = -(2*PI*k)/n;
  complex<double> res  = exp(expoente*j);
  return res; 
}

complex<double> w_k_i(int k, int n){
  complex<double> expoente = (2*PI*k)/n;
  complex<double> res  = exp(expoente*j);
  return res; 
}

vector<complex<double>> xcorr(int n_amostras, int n_funcoes, const vector<vector<double>>& realizacoes){

  //vector<vector<double>> realizacoes(NUM_FUNCOES, vector<double>(N));
  int L = 2*n_amostras;
  vector<vector<complex<double>>> sinal(n_funcoes, vector<complex<double>>(L, 0));
  for (int i=0;i<n_funcoes;i++){
    int n=2;
    //bit-reversal
    //vector<complex<double>> sinal(N); 
    for (int s=0;s<n_amostras;s++){
      int pos = bitwise(s, log2(L));
      sinal[i][pos] = realizacoes[i][s];
    }
    //fft
    while(n<=L){
      for (int k=0; k<L/2; k++){
        int r = k%(n/2);
        complex<double> x_k = sinal[i][2*k -r] + sinal[i][2*k -r + n/2]*w_k(r,n);
        complex<double> x_k_n_2 = sinal[i][2*k -r] - sinal[i][2*k -r + n/2]*w_k(r,n);
        
        sinal[i][2*k -r] = x_k;
        sinal[i][2*k -r+n/2] = x_k_n_2;
      }
      n = n*2;
    }
    for (int n=0;n<L;n++){
      complex<double> v = sinal[i][n];
      sinal[i][n] = pow(v.imag(),2)+pow(v.real(),2);
    }
  }
  //media
  vector<complex<double>> p_media(L);
  for(int k=0;k<L;k++){
    complex<double> soma;
    for(int n=0;n<n_funcoes;n++){
      soma+=sinal[n][k];
    }
    p_media[k] = soma/static_cast<double>(n_funcoes);
  }


  //bit-reversal
  vector<complex<double>> sinal2(L); 
  for (int s=0;s<L;s++){
    int pos = bitwise(s, log2(L));
    sinal2[pos] = p_media[s];

  }
  //ifft
  int n=2;
  while(n<=L){
    for (int k=0; k<L/2; k++){
      int r = k%(n/2);
      complex<double> x_k = sinal2[2*k -r] + sinal2[2*k -r + n/2]*w_k_i(r,n);
      complex<double> x_k_n_2 = sinal2[2*k -r] - sinal2[2*k -r + n/2]*w_k_i(r,n);
      
      sinal2[2*k -r] = x_k;
      sinal2[2*k -r+n/2] = x_k_n_2;
    }
    n = n*2;
  }
    
  for (int s=0;s<n_amostras;s++){
    complex<double>v = sinal2[s];
    sinal2[s] = v/static_cast<double>(L);
  }
  
  vector<complex<double>> res(n_amostras);
  for (int k=0; k<n_amostras;k++){
    res[k] = sinal2[k]/static_cast<double>(n_amostras-k);
  }

  return res;
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
