#include <iostream>

void f() {
  float var_0 = 99.3966;
  float var_1 = 4.44851;
  int var_2 = 94;
  std::cout << "Result of:" << " var_0 / var_1 / var_0" << " = " <<  var_0 / var_1 / var_0 << "\n";
  std::cout << "Result of:" << " var_0 / var_1 / var_0" << " = " <<  var_0 / var_1 / var_0 << "\n";
  std::cout << "Result of:" << " var_0 / var_2 + var_2" << " = " <<  var_0 / var_2 + var_2 << "\n";
}

int main() {
  f();
  return 0;
}
