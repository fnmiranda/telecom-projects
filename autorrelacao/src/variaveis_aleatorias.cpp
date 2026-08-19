#include <cmath>
#include <random>
#include "../include/variaveis_aleatorias.h"
using namespace std;

namespace {
    random_device rd;
    mt19937 gen(rd());
}
double generate_variancia (double snr){
  double potencia_ruido = 1/pow(10,(snr/10.0)); // é 1 no numerdor pq a o potencia da senoide é (sqrt(2)²)/2 
  double variancia = potencia_ruido; //potencia é igual a variancia 
  return variancia;
}

double generate_va_uniforme(double min, double max){
  uniform_real_distribution<double> dist(min,max);
  double res;
  do {
    res  = dist(gen);
  } while (res == 0.0);
  return res;
}

double generate_va_gaussina(double media, double variancia){
  double desvio_padrao = sqrt(variancia);
  normal_distribution<double> dist(media, desvio_padrao);
  double x = dist(gen);
  return x;
}
