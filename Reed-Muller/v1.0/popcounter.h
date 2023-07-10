#include <vector>
#include <string>
#ifndef REED_MULLER_POPCOUNTER_H
#define REED_MULLER_POPCOUNTER_H
namespace Reed_Muller {
  class popcounter {
  public:
    popcounter();
    ~popcounter();
    std::vector<int> operator()(int a);

    std::string to2(int a, int padding);

  };
}

#endif //REED_MULLER_POPCOUNTER_H
