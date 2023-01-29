#include <functional>
#include <iostream>
#include <string>
#include <assert.h>

template<typename T>
struct binary_t {
  typedef const T & value_type;
  typedef T(* type)(value_type, value_type);
};

template<typename T, typename binary_t<T>::type binary_op_add, typename binary_t<T>::type binary_op_sub>
struct C {
  static T add(const T &a, const T &b) { return binary_op_add(a, b); }
  static T sub(const T &a, const T &b) { return binary_op_sub(a, b); }
};

std::string add_str(const std::string &a, const std::string &b)
{ return a + b;
}

std::string sub_str(const std::string &a, const std::string &b)
{ 
  return a.substr(0, a.find(b));
}

int add_int(const int &a, const int &b)
{ return a + b;
}

int sub_int(const int &a, const int &b)
{ return a - b;
}

typedef C<std::string, add_str, sub_str> str_t;
typedef C<int, add_int, sub_int> int_t;

int main(int argc, char **argv)
{
  std::string str_a = "Hello, ";
  std::string str_b = "world!";
  std::string str_c = str_t::add(str_a, str_b);
  std::string str_d = str_t::sub(str_c, str_b);

  int int_a = 8;
  int int_b = 2;
  int int_c = int_t::add(int_a, int_b);
  int int_d = int_t::sub(int_c, int_b);

  std::cout << str_a << " + " << str_b << " = " << str_c << std::endl;
  std::cout << str_c << " - " << str_b << " = " << str_d << std::endl;
  std::cout << std::to_string(int_a) << " + " << std::to_string(int_b) << " = " << std::to_string(int_c) << std::endl;
  std::cout << std::to_string(int_c) << " - " << std::to_string(int_b) << " = " << std::to_string(int_d) << std::endl;
  assert(int_d == int_a);
}
