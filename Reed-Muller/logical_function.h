#include <iostream>
#include <vector>
#ifndef REED_MULLER_LOGICAL_FUNCTION_H
#define REED_MULLER_LOGICAL_FUNCTION_H
namespace Reed_Muller {

    class logical_function {
    public:
        logical_function(int n, std::string truth_table);

        ~logical_function();

        int operator()(std::vector<int> vars);

        void print();

    private:
        //each cell represents the coef * (var_1 & var_2 & ... & var_n), coef is either 0 or 1;
        // variables string looks like "a1 a2 ... an", the delimiter is single space;
        // !THINK OF ANY WAY TO VALIDATE THE STRING OR CHANGE THE FORMAT
        struct cell {
            int coef;
            std::vector<int> variables;
        };
        int num;
        std::vector<cell> func;
    };
}

#endif //REED_MULLER_LOGICAL_FUNCTION_H
