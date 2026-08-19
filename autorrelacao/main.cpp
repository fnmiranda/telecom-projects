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
  auto autocorrelacoes = autocorrelacao(N, NUM_FUNCOES, realizacoes); 

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


  // Nova figura para autocorrelacao
  ptl::figure();

  ptl::named_plot("Autocorrelacao", eixo_x, autocorrelacoes_completo);

  ptl::xlabel("Atraso (s)");
  ptl::ylabel("R_x(tau)");
  ptl::title("Autocorrelacao");
  ptl::legend();
  
  ptl::show();

  return 0;
}
