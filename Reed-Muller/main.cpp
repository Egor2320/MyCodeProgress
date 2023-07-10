#include "popcounter.h"
#include "logical_function.h"

int main() {
  Reed_Muller::popcounter p;

  Reed_Muller::logical_function f(3, "10110001");

  for(int i = 0; i < 8; ++i){
  std::string s = p.to2(i, 3);
  std::cout << s << "->" << f(s) << '\n';
  }

		f.polynomical();


  return 0;
}
