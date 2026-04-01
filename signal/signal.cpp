#include "signal.h"

#include <cmath>

Mensagem criar_mensagem(double ampt_m, double freq_m) {
  Mensagem m;
  m.amplitude_M = ampt_m;
  m.frequencia_M = freq_m;
  return m;
}

Portadora criar_portadora(double ampt_c, double freq_c, Mensagem msg) {
  Portadora p;
  p.amplitude_C = ampt_c;
  p.frequencia_C = freq_c;
  p.mensagem = msg;
  return p;
}

double portadora(const Portadora &portadora, double tempo) {
  double res;
  res = (portadora.amplitude_C +
         portadora.mensagem.amplitude_M *
             cos(2 * PI * portadora.mensagem.frequencia_M * tempo)) *
        cos(2 * PI * portadora.frequencia_C * tempo);
  return res;
}
