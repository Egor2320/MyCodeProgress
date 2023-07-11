#include "Test.h"
namespace Reed_Muller{
	
	void Test::testAll(const std::vector<Cell> &func, const kitty::dynamic_truth_table &t) {
		if(t.num_vars() != func[func.size() - 1].coef)
			throw InvalidFormat("The size of truth table and the function are not equal");
		
		uint64_t base = std::pow(2, t.num_vars());
		for (int i = 0; i < base; ++i){
			std::string s = Helper::to2(i, t.num_vars());
			uint64_t function = LogicalFunction::apply(func, s);
			uint64_t ans = kitty::get_bit(t, i);
			if(function == ans)
				std::cout << s << " -> " << function <<", "<< ans << " => test passed\n";
			else
				std::cout << s << " -> " << function <<", "<< ans << " => test failed\n";
		}
	}
	
	void Test::testRandom(uint64_t size) {
		uint64_t bits = std::pow(2, size);
		kitty::dynamic_truth_table t(size);
		std::string s = Helper::generate(bits);
		kitty::create_from_binary_string(t,s);
		std::vector<Cell> f = Reed_Muller::LogicalFunction::sythesize(t);
		testAll(f, t);
	}
	
	
	
}