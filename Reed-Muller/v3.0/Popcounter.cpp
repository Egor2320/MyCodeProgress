#include "Popcounter.h"
#include <algorithm>
namespace Reed_Muller{
	
	std::vector<int> Popcounter::popcnt(int a) {
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
	
  std::string Popcounter::to2(uint32_t a, uint64_t padding) {
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