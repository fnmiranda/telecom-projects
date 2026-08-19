#include "../include/constantes.h"
#include "../include/sinal.h"
#include <cmath>
#include "../include/variaveis_aleatorias.h"

using namespace constants;
using namespace std;



Sinal criar_sinal(double amplitude, double fase, double fc){
  Sinal s;
  s.amplitude = amplitude;
  s.fase = fase;
  s.fc = fc;
  return s;
}

Ruido criar_ruido(double media, double desvio_padrao){
  Ruido r;
  r.media = media;
  r.desvio_padrao = desvio_padrao;
  return r;
}

double sinal_completo (const Sinal &sinal, const Ruido &ruido, double tempo){
  double sinal_puro = sinal.amplitude*cos(2*PI*sinal.fc*tempo+sinal.fase);
  double w = generate_va_gaussina(ruido.media, ruido.desvio_padrao);
  double x = sinal_puro + w;

  return x;
}
