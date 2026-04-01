#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<double> tensoes = {0, 0.2, 0.4, 0.6, 0.7, 1.0};

  for (double v : tensoes) {
    double res = 1.8 * pow(10, -14) * (exp(v / (8.617 * 0.003)) - 1);
    cout << "I_s = " << res << " | V = " << v << ";\n";
  }

  return 0;
}
