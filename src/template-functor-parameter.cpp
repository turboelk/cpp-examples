#include <functional>
#include <iostream>
#include <string>
#include <assert.h>

template<typename T>
struct C {
  typedef T value_type;
  typedef std::function<T(T, T)> function_type;

  function_type add;
  function_type sub;
  
  C(function_type add, function_type sub)
    : add(add)
    , sub(sub)
  {
  }
};

std::string add_str(const std::string &a, const std::string &b)
{ return a + b;
}

std::string sub_str(const std::string &a, const std::string &b)
{ 
  return a.substr(0, a.find(b));
}

int add_int(int a, int b)
{ return a + b;
}

int sub_int(int a, int b)
{ return a - b;
}

typedef C<std::string> str_c_t;
typedef C<int> int_c_t;

int main(int argc, char **argv)
{
  str_c_t str_t { add_str, sub_str };
  int_c_t int_t { add_int, sub_int };

  std::string str_a = "Hello, ";
  std::string str_b = "world!";
  std::string str_c = str_t.add(str_a, str_b);
  std::string str_d = str_t.sub(str_c, str_b);

  int int_a = 8;
  int int_b = 2;
  int int_c = int_t.add(int_a, int_b);
  int int_d = int_t.sub(int_c, int_b);

  std::cout << str_a << " + " << str_b << " = " << str_c << std::endl;
  std::cout << str_c << " - " << str_b << " = " << str_d << std::endl;
  std::cout << std::to_string(int_a) << " + " << std::to_string(int_b) << " = " << std::to_string(int_c) << std::endl;
  std::cout << std::to_string(int_c) << " - " << std::to_string(int_b) << " = " << std::to_string(int_d) << std::endl;
  assert(int_d == int_a);
}
