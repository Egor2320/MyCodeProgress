#include <vector>
#include <string>
#ifndef REED_MULLER_POPCOUNTER_H
#define REED_MULLER_POPCOUNTER_H
namespace Reed_Muller {
  class Popcounter {
  public:

    static std::vector<int> popcnt(int a);
    static std::string to2(uint32_t a, uint64_t padding);

  };
}

#endif //REED_MULLER_POPCOUNTER_H