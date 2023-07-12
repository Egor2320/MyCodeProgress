#include "helper.h"
#include "reed_muller.h"
#include <algorithm>

namespace Library {
	ReedMuller::ReedMuller() = default;
	ReedMuller::~ReedMuller() = default;
	
	std::vector<Cell> ReedMuller::sythesize(const kitty::dynamic_truth_table& t) {
		uint64_t num_vars = t.num_vars();
		std::vector<Cell> function;
		function.resize(1 << num_vars);
		size_t truth_table_size = 1 << num_vars;
		function[0].coef = kitty::get_bit(t, 0);
		
		for (int i = 1; i < truth_table_size; ++i) {
			std::vector<int> tmp = Helper::popcnt(i);
			function[i].variables = tmp;
			uint64_t cur_num_of_var = tmp.size();
			uint64_t cur_coef = (kitty::get_bit(t, i));
			uint64_t base = 1 << cur_num_of_var;
			
			for(int k = 0; k < base; ++k) {
				std::string s = Helper::to2(k, cur_num_of_var);
				
				int pos = 0;
				
				for (int j = 0; j < s.size(); ++j) {
					if(s[j] == '1') {
						pos += (1 << (tmp[j]));
					}
				}
				cur_coef ^= function[pos].coef;
			}
			function[i].coef = cur_coef;
		}
		
		std::vector<Cell> reduced_function;
		for(const Cell& c : function){
			if(c.coef == 1) reduced_function.push_back(c);
		}
		if(reduced_function.empty()) reduced_function.emplace_back();
		reduced_function.emplace_back();
		reduced_function[reduced_function.size()-1].coef = t.num_vars();
		return reduced_function;
		
	}
	
	//the last cell in func has the number of variables the func depends on as the "coef" field
	uint64_t ReedMuller::apply(const std::vector<Cell> &func, const std::string &s) {
		std::string s_ = s;
		if(s_.size() > func[func.size() - 1].coef) {
			throw InvalidPadding("Too many arguments for the function");
		}
		while(s_.size() < func[func.size() - 1].coef) {
			s_ += "0";
		}
		
		std::reverse(s_.begin(), s_.end());
		uint64_t res = 0;
		for(int i = 0; i < func.size() - 1; ++i) {
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
	
	
	void ReedMuller::polynomical(std::vector<Cell> func) {
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
	
	std::vector<Cell> ReedMuller::sythesize_test(const kitty::dynamic_truth_table &t) {
		std::vector<Cell> char_function;
		uint64_t num_bits = t.num_bits();
		uint64_t num_var = t.num_vars();
		for(int i = 0; i < num_bits; ++i){
			if (kitty::get_bit(t, i) == 1){
				std::vector<int> v = Helper::popcnt(i);
				char_function.emplace_back(1, v);
			}
		}
		char_function.emplace_back();
		char_function[char_function.size() - 1].coef = num_var;
		std::vector<Cell> result_function;
		for(int i = 0; i < num_bits; ++i) {
			uint64_t current = apply(char_function, Helper::to2(i, num_var));
			if(current == 1){
				std::vector<int> v = Helper::popcnt(i);
				result_function.emplace_back(1, v);
			}
		}
		result_function.emplace_back();
		result_function[result_function.size() - 1].coef = num_var;
		return result_function;
	}
}

