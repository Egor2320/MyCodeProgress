#include "popcounter.h"
#include "logical_function.h"

int main() {
    Reed_Muller::popcounter p;
    std::vector<int> v = p(52);

    Reed_Muller::logical_function f(3, "10100111");
    f.print();
    return 0;
}
