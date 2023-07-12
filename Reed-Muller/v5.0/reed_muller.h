#include "kitty-master/include/kitty/kitty.hpp"
#include <iostream>
#include <vector>
#include <unordered_set>

#ifndef REED_MULLER_LOGICAL_FUNCTION_H
#define REED_MULLER_LOGICAL_FUNCTION_H
namespace Library {
	
	 /**
	 * Class Cell represents a subpolinomial q(x_1, x_2, ... , x_n) = a_i & x_a1 & ... x_an \n
	 * Each Cell has a coefficient and a std::vector<int> variables
	 */
	struct Cell {
		/// coeficient of a subpolinomial (either 0 or 1)
		uint64_t coef;
		
		/// array of variables the subpolinomial depends on
		std::vector<int> variables;
		
		/**
		 *
		 * Default constructor \n creates a subpolinomial q(x_1, ... , x_n) = 0
		 *
		 */
		Cell() : coef(0) {};
		/**
		 *
		 * Constructor that creates a subponimoial with coefficient c, that depends on variables from v
		 *
		 */
		Cell(int c, std::vector<int> v): coef(c), variables(std::move(v)) {};
		/**
		 * Default virtual destructor
		 */
		virtual ~Cell() = default;
	};
	
	/**
	* Class LogicalFunction creates a polynomial P(x_1, x_2, ... , x_n) = a_0 ^ (a_1 & x_1) ^ (a_2 & x_2) ^ ... ^ (a_12 & x_1 & x_2) ^ ... by a given truth table
	*/
  class ReedMuller {
  public:
		/**
		 * Default constructor
		 */
		ReedMuller();
		
		/**
		 * Default virtual destructor
		 */
		virtual ~ReedMuller();
		
		/**
		 * Creates a function, represented by a given truth table \n
		 * The result function is stored as a std::vector<Cell> \n
		 * Sample output: \n kitty:create_from_binary_string(TT t, "10011100");\n
		 * 								sythesize(t) = x_2 ^ x_3 ^ x_1 & x_3
		 *
		 * @return std::vector<Cell> func
		 */
		 std::vector<Cell> sythesize(const kitty::dynamic_truth_table& t);
		 std::vector<Cell> sythesize_test(const kitty::dynamic_truth_table& t);
		/**
		* Prints the polynomical representation of a given function \n
		* Sample output:  \n kitty:create_from_binary_string(TT t, "10011100");\n
		* 								std::vector<Cell> f = sythesize(t);\n
		* 								polynomical(f) = x_2 ^ x_3 ^ x_1 & x_3
		*
 		*/
    void polynomical(std::vector<Cell> func);
	  
	  
	   /**
		 * Applies the given function to a given binary string \n
	   * Before applying the function checks whether the size of a given binary string is right (is the same, as the number of variables)\n
	   * If s.size() < num_vars -> add leading zeroes to make the padding right \n
	   * If s.size() > num_vars -> throw an InvalidPadding excepton (it's a custom exception of class LogicalFunction)
	   *
	   * @return uint64_t ans
		 */
		uint64_t apply(const std::vector<Cell> &func, const std::string &s);
		
	private:
	  class InvalidPadding : public std::exception{
		  public:
		  InvalidPadding(const char *message) : _description(message) {};
		  const char * what() const noexcept override {
			  return _description;
		  }
		  private:
		  const char * _description;
	  };
		
  };
}

#endif //REED_MULLER_LOGICAL_FUNCTION_H