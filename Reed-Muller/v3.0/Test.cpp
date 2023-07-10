#include "Test.h"
namespace Reed_Muller{
	
	void Test::testFunc(const std::vector<Cell>& func, const kitty::dynamic_truth_table& t, uint32_t num) {
		int padd = t.num_vars();
		for (int i = 0; i < num; i++){
			std::mt19937 engine;
			std::random_device device;
			engine.seed(device());
			
			uint32_t val = engine() % static_cast<uint32_t>(pow(2, padd));
			std::string s = Popcounter::to2(val, padd);
			
			
			uint64_t ans = LogicalFunction::apply(func, s);
			if(ans == kitty::get_bit(t,val))
				std::cout << val << ": "<< s << ' ' << ans << ' ' << kitty::get_bit(t, val) << "-> test passed\n";
			else
				std::cout << val << ": "<< s << ' ' << ans << ' ' << kitty::get_bit(t, val) << "-> test failed\n";
		}
	}
	
}