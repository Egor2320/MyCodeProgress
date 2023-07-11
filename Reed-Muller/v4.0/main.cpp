#include "Helper.h"
#include "LogicalFunction.h"
#include "Test.h"

int main() {
	
	
	kitty::dynamic_truth_table t(3);
	kitty::create_from_binary_string(t, "10011100");
	std::vector<Reed_Muller::Cell> f = Reed_Muller::LogicalFunction::sythesize(t);
	Reed_Muller::LogicalFunction::polynomical(f);
	return 0;
}