#include "popcounter.h"
#include "logical_function.h"

int main() {
    Reed_Muller::popcounter p;

    Reed_Muller::logical_function f(4, "1010011011110001");

    for(int i = 0; i < 16; ++i){
        std::string s = p.to2(i, 4);
        std::cout << s << "->" << f(s) << '\n';
    }


    f.print();


    return 0;
}
