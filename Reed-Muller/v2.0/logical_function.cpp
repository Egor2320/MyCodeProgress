#include "logical_function.h"
#include "popcounter.h"
#include <cmath>
#include <algorithm>

namespace Reed_Muller{
	
	logical_function::logical_function(int n, const kitty::dynamic_truth_table &t) {
		popcounter p;
		
		std::vector<cell> func_tmp;
		num = n;
		func_tmp.resize(pow(2, n));
		size_t len = pow(2, n);
		func_tmp[0].coef = kitty::get_bit(t, 0);
		for (int i = 1; i < len; ++i){
			std::vector<int> tmp = p(i);
			func_tmp[i].variables = tmp;
			uint64_t cur_num_of_var = tmp.size();
			uint64_t cur_coef = (kitty::get_bit(t, i));
			for(int k = 0; k < pow(2, cur_num_of_var); ++k){
				std::string s = p.to2(k, cur_num_of_var);
				
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
		
		for(const cell& c : func_tmp){
			if(c.coef == 1) func.push_back(c);
		}
		
		
	}
	
	uint64_t logical_function::operator()(const kitty::dynamic_truth_table& t) {
		uint64_t res = 0;
		for (auto &i: func) {
			uint64_t carry = 1;
			for (auto variable : i.variables) {
				carry &= kitty::get_bit(t, variable);
			}
			//carry &= i.coef;
			res ^= carry;
		}
		return res;
	}
	
	
	void logical_function::polynomical() {
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
	
	logical_function::~logical_function() = default;
	
	std::vector<cell> logical_function::sythesize(kitty::dynamic_truth_table t) {
		popcounter p;
		int n = t.num_vars();
		std::vector<cell> func_tmp;
		func_tmp.resize(pow(2, n));
		size_t len = pow(2, n);
		func_tmp[0].coef = kitty::get_bit(t, 0);
		for (int i = 1; i < len; ++i){
			std::vector<int> tmp = p(i);
			func_tmp[i].variables = tmp;
			uint64_t cur_num_of_var = tmp.size();
			uint64_t cur_coef = (kitty::get_bit(t, i));
			for(int k = 0; k < pow(2, cur_num_of_var); ++k){
				std::string s = p.to2(k, cur_num_of_var);
				
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
		std::vector<cell> func_;
		for(const cell& c : func_tmp){
			if(c.coef == 1) func_.push_back(c);
		}
		return func_;
		
	}
	
	//additional functions;
	logical_function::logical_function(int n, std::string truth_table) {
		kitty::dynamic_truth_table t(n);
		kitty::create_from_binary_string(t, truth_table);
		*this = logical_function(n, t);
	}
	
	uint64_t logical_function::operator()(std::string s) {
		kitty::dynamic_truth_table t(std::log2(num));
		kitty::create_from_binary_string(t, s);
		return operator()(t);
	}
	
	uint64_t logical_function::operator()(std::vector<int> v) {
		kitty::dynamic_truth_table t(std::log2(num));
		for(int i = 0; i < v.size(); ++i){
			if(v[i] == 1) kitty::set_bit(t, i);
			else kitty::clear_bit(t, i);
		}
		return operator()(t);
	}
	
}

