#include "../include/export.h"
#include <fstream>
#include <ios>
using namespace std;

void salvar_csv(const char *nome_arquivo, double tempo, double result) {
  ofstream arquivo;
  arquivo.open(nome_arquivo, ios::app);

  arquivo << tempo << "," << result << "\n";
  arquivo.close();
}
