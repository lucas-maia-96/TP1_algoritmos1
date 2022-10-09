#include <iostream>

int main() {
  int a, b;
  bool na, nb;
  a = -6;
  b = -7;
  na = true;
  nb = true;
  a *= -1;
  b *= -1;
  a = 2 * a ^ na;
  b = 2 * b ^ nb;
  int neg_a = a ^ 1;
  int neg_b = b ^ 1;
  std::cout << a << " " << b;
}