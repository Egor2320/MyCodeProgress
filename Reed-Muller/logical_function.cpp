//
// Created by ПК on 09.07.2023.
//

#include "logical_function.h"
#include "popcounter.h"

namespace Reed_Muller{
    logical_function::logical_function(int n, std::string truth_table) {
        popcounter p;
        func.resize(n);
        int len = truth_table.size();
        func[0].coef = truth_table[0] - '0';
        for (int i = 1; i < len; ++i){
            func[i].variables = p(i);
            /*for (int j = 0; j < i; ++j){

            }*/
        }
    }

    logical_function::~logical_function() = default;

}
