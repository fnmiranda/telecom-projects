#include "export.h"
#include "signal.h"
#include <iostream>
using namespace std;

int main() {

  Portadora port = criar_portadora(1.0, 10000.0, criar_mensagem(0.5, 500.0));
  double tempo = 0.0;

  while (tempo < 0.01) {
    double port_value = portadora(port, tempo);
    cout << "tempo: " << tempo << ", valor: " << port_value << ";\n";
    salvar_csv("resultados.csv", tempo, port_value);
    tempo += 1.0 / (20 * port.frequencia_C);
  }

  return 0;
}
