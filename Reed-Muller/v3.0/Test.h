#include <random>
#include "kitty-master/include/kitty/kitty.hpp"
#include "Popcounter.h"
#include "LogicalFunction.h"
#ifndef REED_MULLER_TEST_H
#define REED_MULLER_TEST_H

namespace Reed_Muller {
	class Test {
	public:
		static void testFunc (const std::vector<Cell>& func, const kitty::dynamic_truth_table& t, uint32_t num);
	};
}


#endif //REED_MULLER_TEST_H
