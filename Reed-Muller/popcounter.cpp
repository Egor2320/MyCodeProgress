#include "popcounter.h"
namespace Reed_Muller{

    popcounter::popcounter() = default;
    popcounter::~popcounter() = default;



    std::vector<int> popcounter::operator()(int a) {
        std::vector<int> res;
        int count = 0;

        while(a != 0){
            int mask = 0x1;
            mask &= a;
            if(mask == 1) res.push_back(count);
            ++count;
            a = a >> 1;
        }
        return res;
    }

}