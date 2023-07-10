#include "Popcounter.h"
#include "LogicalFunction.h"
#include "Test.h"
int main() {
  kitty::dynamic_truth_table t(2);
  std::string s = "0000";
  //std:: string test = "1011";
  kitty::create_from_binary_string(t, s);
	
	std::vector<Reed_Muller::Cell> f = Reed_Muller::LogicalFunction::sythesize(t);
	/*
	Reed_Muller::LogicalFunction::polynomical(f);
  std::cout << '\n';
	kitty::dynamic_truth_table table(2);
	kitty::create_from_binary_string(table, test);
	std::cout << Reed_Muller::LogicalFunction::apply(f, table) << '\n';
	for(int i = 0; i < 16; ++i){
		kitty::dynamic_truth_table tmp(2);
		std::string str = Reed_Muller::Popcounter::to2(i, 4);
		kitty::create_from_binary_string(tmp, str);
		std::cout << str << "->" << Reed_Muller::LogicalFunction::apply(f, str) << '\n';
		
	}*/
	Reed_Muller::LogicalFunction::polynomical(f);
	std::cout << '\n';
	Reed_Muller::Test::testFunc(f, t, 1000);
	
	
  return 0;
}