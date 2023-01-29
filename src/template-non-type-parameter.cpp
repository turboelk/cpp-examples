#include <iostream>
#include <string>
#include <assert.h>

template<int I>
struct integral {
  static constexpr int value() { return I; }
};

template<int I>
struct foo {
  typedef integral<I> bar;
};

int main(int argc, char **argv)
{
  std::cout << std::to_string(foo<5>::bar::value()) << std::endl;
}
