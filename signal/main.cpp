#define WITHOUT_NUMPY
#include "include/export.h"
#include "include/matplotlibcpp.h"
#include "include/signal.h"
#include <iostream>
#include <vector>

using namespace std;
namespace ptl = matplotlibcpp;

int main() {
  vector<double> tempos;
  vector<double> valores;

  Portadora port = criar_portadora(1.0, 10000.0, criar_mensagem(0.5, 500.0));
  double tempo = 0.0;

  while (tempo < 0.01) {
    double port_value = portadora(port, tempo);
    cout << "tempo: " << tempo << ", valor: " << port_value << ";\n";
    salvar_csv("resultados.csv", tempo, port_value);

    tempos.push_back(tempo);
    valores.push_back(port_value);
    tempo += 1.0 / (20 * port.frequencia_C);
  }

  ptl::plot(tempos, valores);
  ptl::show();

  return 0;
}
