#include "logical_function.h"
#include "popcounter.h"
#include <cmath>
namespace Reed_Muller{
    logical_function::logical_function(int n, std::string truth_table) {
        popcounter p;

        num = n;
        func.resize(pow(2, n));
        int len = truth_table.size();
        func[0].coef = truth_table[0] - '0';
        for (int i = 1; i < len; ++i){
            std::vector<int> tmp = p(i);
            func[i].variables = tmp;
            int cur_num_of_var = tmp.size();
            int cur_coef = (truth_table[i] - '0');
            for(int k = 0; k < pow(2, cur_num_of_var); ++k){
                std::string s = p.to2(k, cur_num_of_var);
                //std::cout << "debug (double) " << s << '\n';
                int pos = 0;
                for (int j = 0; j < s.size(); ++j){
                    if(s[j] == '1'){
                        pos += (1 << (tmp[j]));
                    }
                }
                //std::cout << "debug " << pos << '\n';
                cur_coef ^= func[pos].coef;
            }
            func[i].coef = cur_coef;
        }
    }

    logical_function::~logical_function() = default;

    void logical_function::print() {
        for (int i = 0; i < func.size(); ++i){
            std::cout << func[i]. coef << '\n';
            if(!i) std::cout << "no args ";
            else std::cout << "args: ";
            for (int j = 0; j < func[i].variables.size(); ++j){
                std::cout << func[i].variables[j] + 1 << ' ';
            }
            std::cout << '\n';
        }
    }

}
