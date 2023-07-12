#include "helper.h"
#include "kitty-master/include/kitty/kitty.hpp"
#include "reed_muller.h"
#include <random>

#ifndef REED_MULLER_TEST_H
#define REED_MULLER_TEST_H

namespace Library {
	///Class Test runs the test to check if the implementation of Reed-Muller approach is correct
	class Test {
	public:
		 /**
		 * Compares all the possible values that func can produce to a given truth table and tells whether they are the same\n
		 * If sizes of truth table and func.num_vars are not the same, throws an InvalidFormat exception (it's a custom exception of class Test)
		 *
		 */
		static void testAll (const std::vector<Cell>& func, const kitty::dynamic_truth_table& t);
		
		 /**
		 * Generates a random binary string of length 2^size, creates a truth table by it and a function by the truth table \n
		 * Then runs the testAll() function to see if the function is correct
		 *
		 */
		static void testRandom(uint64_t size);
		
		static void testTwo(std::vector<Cell> f1, std::vector<Cell> f2);
		
	private:
		
		class InvalidFormat : public std::exception {
			public:
			InvalidFormat(const char *message) : _description(message) {};
			const char * what()const noexcept override {
				return _description;
			}
			
			private:
			const char * _description;
		};
	};
}


#endif //REED_MULLER_TEST_H
