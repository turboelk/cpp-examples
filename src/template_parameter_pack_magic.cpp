#include <iostream>
#include <string>
#include <assert.h>

template<int, typename ...>
struct validate_t {
};

template<int I, typename Head>
struct validate_t<I, Head> {

  template<typename V, typename ...ArgV>
  static bool all(V fn, ArgV &&...args)
  { Head *_default = nullptr;
    return fn(I, _default, args...);
  }
};

template<int I, typename Ht, typename ...Tt>
struct validate_t<I, Ht, Tt...> {
  typedef validate_t<I, Ht>         head_type;
  typedef validate_t<I + 1, Tt...>  tail_type;

  template<typename V, typename ...ArgV>
  static bool all(V fn, ArgV &&...args)
  { return head_type::all(fn, args...)
      && tail_type::all(fn, args...);
  }
};

template<typename ...T>
using validate = validate_t<0, T...>;

int main(int argc, char **argv)
{
  std::string message = "Hello, world!";
  std::cout << std::boolalpha;

#define remove_pointer(x) std::remove_pointer<decltype(x)>::type
#define is_same(x, y) std::is_same<x, y>::value

  auto validator = [](int i, auto *_default, std::string msg) -> bool {
    typedef typename remove_pointer(_default) type;
    return is_same(type, std::string)
      || is_same(type, long)
      || is_same(type, unsigned)
      || is_same(type, int)
      || is_same(type, char)
      || is_same(type, double)
      || is_same(type, bool);
  };

  if (validate<std::string, long, unsigned, int, char, double, bool>::all(validator, message))
    std::cout << "Correct" << std::endl;
}
