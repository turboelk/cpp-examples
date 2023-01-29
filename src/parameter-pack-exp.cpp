#include <iostream>
#include <string>
#include <functional>

typedef const char * str;

inline void exp(str t)
{
  std::cout << "exp('" << t << "')" << std::endl;
}

template<typename arg_t, typename ...args_t>
inline void exp(str t, arg_t arg, args_t ...args)
{
  std::cout << "exp<...>('" << t << "', ...)" << std::endl;
  exp(arg, args...);
}

struct _Exp {
  template<typename arg_t>
  _Exp(arg_t arg) {
    std::cout << "_Exp::_Exp('" << arg << "')" << std::endl;
  }

  template<typename arg_t, typename ...args_t>
  _Exp(arg_t arg, args_t ...args) {
    std::cout << "_Exp::_Exp<arg_t, ...>('" << arg << "', ...)" << std::endl;
    _Exp(args...);
  }
};

template<typename ...args_t>
void _ExpTest(args_t ...args)
{
  std::cout << "_ExpTest(...)" << std::endl;
  exp(args...);

  _Exp(args...);
}

int main(int argc, char **argv)
{
  exp("Hello", ", world!");
  _ExpTest("Hello", ", world!");
}
