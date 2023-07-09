#include "popcounter.h"
#include <algorithm>
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

    std::string popcounter::to2(int a, int padding) {
        if(!a){
            int size = 0;
            std::string ans;
            while(size < padding){
                ans+='0';
                ++size;
            }
            return ans;
        }
        std::string res;
        int size = 0;
        while(a != 0){
            res += std::to_string(a % 2);
            a /= 2;
            ++size;
        }
        while(size < padding){
            res += '0';
            ++size;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }

}
