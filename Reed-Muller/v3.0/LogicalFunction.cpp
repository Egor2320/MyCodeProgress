#include "LogicalFunction.h"
#include "Popcounter.h"
#include <cmath>
#include <algorithm>

namespace Reed_Muller{
	
	std::vector<Cell> LogicalFunction::sythesize(const kitty::dynamic_truth_table& t) {
		
		int n = t.num_vars();
		std::vector<Cell> func_tmp;
		func_tmp.resize(pow(2, n));
		size_t len = pow(2, n);
		func_tmp[0].coef = kitty::get_bit(t, 0);
		for (int i = 1; i < len; ++i){
			std::vector<int> tmp = Popcounter::popcnt(i);
			func_tmp[i].variables = tmp;
			uint64_t cur_num_of_var = tmp.size();
			uint64_t cur_coef = (kitty::get_bit(t, i));
			for(int k = 0; k < pow(2, cur_num_of_var); ++k){
				std::string s = Popcounter::to2(k, cur_num_of_var);
				
				int pos = 0;
				for (int j = 0; j < s.size(); ++j){
					if(s[j] == '1'){
						pos += (1 << (tmp[j]));
					}
				}
				
				cur_coef ^= func_tmp[pos].coef;
			}
			func_tmp[i].coef = cur_coef;
			
		}
		std::vector<Cell> func_;
		for(const Cell& c : func_tmp){
			if(c.coef == 1) func_.push_back(c);
		}
		return func_;
		
	}
	
	uint64_t LogicalFunction::apply_to_vec(const std::vector<Cell> &func, std::vector<int> v) {
		std::reverse(v.begin(), v.end());
		int res = 0;
		for(auto & i : func){
			int carry = 1;
			for(int variable : i.variables){
				carry &= v[variable];
			}
			carry &= i.coef;
			res ^= carry;
		}
		return res;
	}
	
	uint64_t LogicalFunction::apply(const std::vector<Cell> &func, const std::string &s) {
		std::vector<int> v;
		size_t len = s.size();
		for(size_t i = 0; i < len; ++i){
			v.push_back(s[i] - '0');
		}
		return LogicalFunction::apply_to_vec(func, v);
	}
	
	
	void LogicalFunction::polynomical(std::vector<Cell> func) {
		for(int i = 0; i < func.size(); ++i){
			if(i == 0 && func[0].variables.empty()){
				std::cout << "1 ";
			}
			for(int variable : func[i].variables){
				std::cout << "x_" << variable + 1 << ' ';
			}
			
			if(i != func.size() - 1)std::cout << "^ ";
			
		}
	}
}

