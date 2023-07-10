#include "popcounter.h"
#include "logical_function.h"

int main() {
 Reed_Muller::popcounter p;
 kitty::dynamic_truth_table t(4);
 std::string s = "0011110100110111";
 
 kitty::create_from_binary_string(t, s);
 std::vector<int> v = {0,0,1,1,1,1,0,1,0,0,1,1,0,1,1,1};
 Reed_Muller::logical_function f(4, t);

 
 for(int i = 0; i < 16; ++i){
	 kitty::dynamic_truth_table tmp(2);
	 std::string str = p.to2(i, 4);
	 kitty::create_from_binary_string(tmp, str);
	 std::cout << str << "->" << f(str) << ',' << f(tmp) << '\n';
	 
 }
 f.polynomical();
 return 0;
}