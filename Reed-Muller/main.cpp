#include <iostream>
#include "popcounter.h"
#include "logical_function.h"

int main() {
    Reed_Muller::popcounter p;
    std::vector<int> v = p(52);
    for(int i = 0; i < v.size(); ++i){
        std::cout << v[i] << ' ';
    }
    return 0;
}
