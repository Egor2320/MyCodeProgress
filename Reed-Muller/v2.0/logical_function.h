#include <iostream>
#include <vector>
#include "kitty-master/include/kitty/kitty.hpp"
#ifndef REED_MULLER_LOGICAL_FUNCTION_H
#define REED_MULLER_LOGICAL_FUNCTION_H
namespace Reed_Muller {
	//represents the ai & (x_a1 & x_a2 & ... & x_an)
	struct cell {
		uint64_t coef;
		std::vector<int> variables;
		
		cell() {
			coef = 0;
		}
		
		cell(int c, std::vector<int> v): coef(c), variables(std::move(v)){};
	};
	//class with static methods
  class logical_function {
  public:
		
    logical_function(int n, std::string truth_table);
    logical_function(int n, const kitty::dynamic_truth_table& t);
		

    ~logical_function();

		
    uint64_t operator()(const kitty::dynamic_truth_table& t);
    uint64_t operator()(std::vector<int> vars);
    uint64_t operator()(std::string);

    void polynomical();

  private:
    //each cell represents the coef * (var_1 & var_2 & ... & var_n), coef is either 0 or 1;
    // variables string looks like "a1 a2 ... an", the delimiter is single space;
    // !THINK OF ANY WAY TO VALIDATE THE STRING OR CHANGE THE FORMAT
		
    int num;
    std::vector<cell> func;
  };
}

#endif //REED_MULLER_LOGICAL_FUNCTION_H
