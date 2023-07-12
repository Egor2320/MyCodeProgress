#include <string>
#include <vector>

#ifndef REED_MULLER_POPCOUNTER_H
#define REED_MULLER_POPCOUNTER_H
namespace Library {
	///Helper is a class, that does all the necessary function for other classes
  class Helper {
  public:
		 /**Generates the vector<int> v, where v[i] is a position of some "1" in a (in binary) \n
		 *Sample output: \n popcnt(6) = {1,2} as 6 in binary is "1100"
		 *
		 * @return std::vector<int> v
		 */
    static std::vector<int> popcnt(int a);
		
	   /**Generates binary representation of a number with a padding \n
		 *Sample output: \n to2(6, 4) = "1100", to2(4, 4) = "0100", to2(6,3) = "1100"
		 *
		 * @return std::string s
		 */
    static std::string to2(uint32_t a, uint64_t padding);
		
	  /**Generates a random binary string of length "bits" \n
    *Sample output:\n generate(8) = "11010101"
 		* @return std::string s
 		*/
		static std::string generate(uint64_t bits);
		
  };
}

#endif //REED_MULLER_POPCOUNTER_H