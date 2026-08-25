#include "./include/constantes.h"
#include "./include/autocorrelacao.h"
#include "./include/matplotlibcpp.h"
#include "./include/variaveis_aleatorias.h"

#include <vector>
#include <chrono>

using namespace constants;

namespace ptl = matplotlibcpp;

int main (){
  vector<int> SNR = {0,5,15};
  //vector<vector<double>> realizacoes(NUM_FUNCOES, vector<double>(N));
  //vector<double> tempos(N);
  //vector<double> autocorrelacoes(N);

  auto start = chrono::high_resolution_clock::now();
  auto tempos = gerar_vetor_atrasos(N);
  auto realizacoes = gerar_matriz_de_sinais(NUM_FUNCOES, N, generate_variancia(SNR[2]));
  //O metodo abaixo é o padrão usando o algoritmo de complexidade O[MN²]
  //auto autocorrelacoes = autocorrelacao(N, NUM_FUNCOES, realizacoes); 

  //Já esté outro metodo xcorr usa o conceito de FFT e IFFT pra reduzir a complexidade pra O[MNlog(M)]
  auto autocorrelacoes_complexa = xcorr(N, NUM_FUNCOES, realizacoes); 
  vector<double> autocorrelacoes(N);
  for (int k=0;k<N;k++){
    autocorrelacoes[k] = autocorrelacoes_complexa[k].real();
  }
  auto [eixo_x, autocorrelacoes_completo] = gerar_vetores_completos(tempos, autocorrelacoes, -300, 300);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> duration = end - start;
  cout << "Tempo de execucao no C++: " << duration.count() << " segundos" << std::endl;

  // Gráfico das 3 realizações
  ptl::figure();

  ptl::named_plot("Realizacao 1", tempos, realizacoes[0]);
  ptl::named_plot("Realizacao 2", tempos, realizacoes[1]);
  ptl::named_plot("Realizacao 3", tempos, realizacoes[2]);

  ptl::xlabel("Tempo (s)");
  ptl::ylabel("X(t)");
  ptl::title("Funcoes amostrais");
  ptl::legend();
  ptl::save("graficos/realizacao.png");

  // Nova figura para autocorrelacao
  ptl::figure();

  ptl::named_plot("Autocorrelacao", eixo_x, autocorrelacoes_completo);

  ptl::xlabel("Atraso (s)");
  ptl::ylabel("R_x(tau)");
  ptl::title("Autocorrelacao");
  ptl::legend();
  
  ptl::save("graficos/autocorrelacao.png");
  ptl::show();

  return 0;
}
