#pragma once

const double PI = 3.141592653589793;
// AM modulation

struct Mensagem {
  double amplitude_M;
  double frequencia_M;
};

struct Portadora {
  double amplitude_C;
  double frequencia_C;
  Mensagem mensagem;
};

Mensagem criar_mensagem(double ampt_m, double freq_m);
Portadora criar_portadora(double ampt_c, double freq_c, Mensagem msg);

double portadora(const Portadora &portadora, double tempo);
