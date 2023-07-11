#include "Helper.h"
#include <algorithm>
#include <random>
namespace Reed_Muller{
	
	
	std::vector<int> Helper::popcnt(int a) {
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
	
  std::string Helper::to2(uint32_t a, uint64_t padding) {
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
	
	void Helper::reverseString(std::string &s) {
		size_t n = s.size();
		for(int i = 0; i < n/2; ++i){
			char c = s[i];
			s[i] = s[n-1-i];
			s[n-1-i] = c;
		}
	}
	
	std::string Helper::generate(uint64_t bits) {
		std::mt19937 engine;
		std::random_device device;
		engine.seed(device());
		std::string s;
		while (s.size() < bits){
			s += (engine() % 2) + '0';
		}
		return s;
	}
}