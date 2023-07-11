#include "LogicalFunction.h"
#include "Helper.h"
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
			std::vector<int> tmp = Helper::popcnt(i);
			func_tmp[i].variables = tmp;
			uint64_t cur_num_of_var = tmp.size();
			uint64_t cur_coef = (kitty::get_bit(t, i));
			uint64_t base = pow(2, cur_num_of_var);
			for(int k = 0; k < base; ++k){
				std::string s = Helper::to2(k, cur_num_of_var);
				
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
		if(func_.empty()) func_.emplace_back();
		func_.emplace_back();
		func_[func_.size()-1].coef = t.num_vars();
		return func_;
		
	}
	
	//the last cell in func has the number of variables the func depends on as the "coef" field
	uint64_t LogicalFunction::apply(const std::vector<Cell> &func, const std::string &s) {
		std::string s_ = s;
		if(s_.size() > func[func.size() - 1].coef){
			throw InvalidPadding("Too many arguments for the function");
		}
		while(s_.size() < func[func.size() - 1].coef){
			s_ += "0";
		}
		
		Helper::reverseString(s_);
		uint64_t res = 0;
		for(int i = 0; i < func.size() - 1; ++i){
			uint64_t carry = 1;
			for(int variable : func[i].variables) {
				if(s_[variable] == '0'){
					carry = 0;
					break;
				}
			}
			carry &= func[i].coef;
			res ^= carry;
		}
		return res;
	}
	
	
	void LogicalFunction::polynomical(std::vector<Cell> func) {
		if(func.size() == 2 && func[0].coef == 0){
			std::cout << "0";
			return;
		}
		for(int i = 0; i < func.size()-1; ++i){
			if(i == 0 && func[0].variables.empty()){
				std::cout << "1 ";
			}
			for(int variable : func[i].variables){
				std::cout << "x_" << variable + 1 << ' ';
			}
			
			if(i != func.size() - 2)std::cout << "^ ";
			
		}
	}
}

