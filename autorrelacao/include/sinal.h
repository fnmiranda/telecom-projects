#pragma once

struct Sinal {
  double amplitude;
  double fase;
  double fc;
};
struct Ruido {
  double media;
  double desvio_padrao;
};

Sinal criar_sinal(double amplitude, double fase, double fc);

Ruido criar_ruido(double media, double variancia);

double sinal_completo(const Sinal &sinal,const Ruido &ruido, double tempo);
