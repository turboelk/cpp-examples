#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

template<typename Rt, typename ...Rp>
struct pack {
  void call(Rp &&...)
  {
    std::cout << "10 pack<Rt, Rt...>::call => \t" << __PRETTY_FUNCTION__ << std::endl;
  }
};

template<typename Rt, typename Fp, typename ...Rp>
struct pack<Rt, Fp, Rp...> {
  void call(Fp &&, Rp &&...)
  {
    std::cout << "18 pack<Rt, Fp, Rp...>::call => \t" << __PRETTY_FUNCTION__ << std::endl;
  }
};

template<typename Fp, typename ...Rp>
struct pack<void, Fp, Rp...> {
  void call(Fp &&, Rp &&...)
  {
    std::cout << "26 pack<void, Fp, Rp...>::call => \t" << __PRETTY_FUNCTION__ << std::endl;
  }
};

int main(int argc, char **argv)
{
  typedef pack<void> _0;
  typedef pack<void, int> _1;
  typedef pack<int> _2;
  typedef pack<int, int> _3;

  _0 i0;
  _1 i1;
  _2 i2;
  _3 i3;

  i0.call();
  i1.call(1);
  i2.call();
  i3.call(1);
}
