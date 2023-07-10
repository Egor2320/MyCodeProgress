#include "logical_function.h"
#include "popcounter.h"
#include <cmath>
#include <algorithm>

namespace Reed_Muller{
  logical_function::logical_function(int n, std::string truth_table) {
  popcounter p;

  std::vector<cell> func_tmp;
  num = n;
    func_tmp.resize(pow(2, n));
    size_t len = truth_table.size();
    func_tmp[0].coef = truth_table[0] - '0';
    for (int i = 1; i < len; ++i){
      std::vector<int> tmp = p(i);
      func_tmp[i].variables = tmp;
      int cur_num_of_var = tmp.size();
      int cur_coef = (truth_table[i] - '0');
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

  logical_function::~logical_function() = default;

  int logical_function::operator()(std::vector<int> v) {
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

  int logical_function::operator()(std::string s) {
    std::vector<int> v;
    size_t len = s.size();
    for(size_t i = 0; i < len; ++i){
      v.push_back(s[i] - '0');
    }
    return logical_function::operator()(v);
  }

  void logical_function::polynomical() {
    for(int i = 0; i < func.size(); ++i){
      if(i == 0){
        std::cout << "1 ";
      }
      for(int variable : func[i].variables){
        std::cout << "x_" << variable + 1 << ' ';
      }
      if(i != func.size() - 1)std::cout << "^ ";

    }
  }

}
