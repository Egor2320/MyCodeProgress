#include <vector>
#ifndef REED_MULLER_POPCOUNTER_H
#define REED_MULLER_POPCOUNTER_H
namespace Reed_Muller {
    class popcounter {
    public:
        popcounter();
        ~popcounter();
        std::vector<int> operator()(int a);
    };
}

#endif //REED_MULLER_POPCOUNTER_H
