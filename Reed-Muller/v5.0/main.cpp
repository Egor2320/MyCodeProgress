#include "helper.h"
#include "reed_muller.h"
#include "test.h"

int main() {
	
	Library::ReedMuller r;
	kitty::dynamic_truth_table t(10);
	std::string s = Library::Helper::generate(1<<10);
	kitty::create_from_binary_string(t, s);
	std::vector<Library::Cell> f = r.sythesize(t);
	std::vector<Library::Cell> g = r.sythesize_test(t);
	Library::Test::testTwo(f, g);
	return 0;

}