#include "test.h"
namespace Library{
	
	void Test::testAll(const std::vector<Cell> &func, const kitty::dynamic_truth_table &t) {
		if(t.num_vars() != func[func.size() - 1].coef)
			throw InvalidFormat("The size of truth table and the function are not equal");
		Library::ReedMuller r;
		uint64_t base = 1 << t.num_vars();
		for (int i = 0; i < base; ++i){
			std::string s = Helper::to2(i, t.num_vars());
			uint64_t function =r.apply(func, s);
			uint64_t ans = kitty::get_bit(t, i);
			if(function == ans)
				std::cout << s << " -> " << function <<", "<< ans << " => test passed\n";
			else
				std::cout << s << " -> " << function <<", "<< ans << " => test failed\n";
		}
	}
	
	void Test::testRandom(uint64_t size) {
		Library::ReedMuller r;
		uint64_t bits = 1 << size;
		kitty::dynamic_truth_table t(size);
		std::string s = Helper::generate(bits);
		kitty::create_from_binary_string(t,s);
		std::vector<Cell> f = r.sythesize_test(t);
		testAll(f, t);
	}
	
	void Test::testTwo(std::vector<Cell> f1, std::vector<Cell> f2) {
		if(f1[f1.size() - 1].coef != f2[f2.size() - 1].coef) throw InvalidFormat("Different sizes of variables");
		
		ReedMuller r;
		uint64_t num_bits = 1 << f1[f1.size() - 1].coef;
		for(int i = 0; i < num_bits; ++i){
			std::string s = Helper::to2(i, f1[f1.size() - 1].coef);
			uint64_t a = r.apply(f1, s);
			uint64_t b = r.apply(f2, s);
			if(a == b)
				std::cout << s << " -> " << a <<", "<< b << " => test passed\n";
			else
				std::cout << s << " -> " << a <<", "<< b << " => test failed\n";
		}
	}
	
	
	
}