#include <iostream>
#include <vector>
#include "kitty-master/include/kitty/kitty.hpp"
#ifndef REED_MULLER_LOGICAL_FUNCTION_H
#define REED_MULLER_LOGICAL_FUNCTION_H
namespace Reed_Muller {
	//represents the ai & (x_a1 & x_a2 & ... & x_an)
	struct Cell {
		uint64_t coef;
		std::vector<int> variables;
		
		Cell() {
			coef = 0;
		}
		
		Cell(int c, std::vector<int> v): coef(c), variables(std::move(v)){};
	};
	
	//class with static methods
  class LogicalFunction {
  public:
		
		static std::vector<Cell> sythesize(const kitty::dynamic_truth_table& t);
		static uint64_t apply(const std::vector<Cell>& func, const std::string &s);
    		static void polynomical(std::vector<Cell> func);
		
	private:
		static uint64_t apply_to_vec(const std::vector<Cell>& func, const std::vector<int> v);
		
  };
}

#endif //REED_MULLER_LOGICAL_FUNCTION_H
