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
    int operator()(std::string);

    void polynomical();

  private:
    //each cell represents the coef * (var_1 & var_2 & ... & var_n), coef is either 0 or 1;
    // variables string looks like "a1 a2 ... an", the delimiter is single space;
    // !THINK OF ANY WAY TO VALIDATE THE STRING OR CHANGE THE FORMAT
    struct cell {
      int coef;
      std::vector<int> variables;

      cell() {
        coef = 0;
      }

      cell(int c, std::vector<int> v): coef(c), variables(std::move(v)){};
    };
    int num;
    std::vector<cell> func;
  };
}

#endif //REED_MULLER_LOGICAL_FUNCTION_H
