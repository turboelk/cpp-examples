#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

struct base_t {
  virtual void print() {}
};

struct public_inh_t : public base_t {
  std::string text;

  public_inh_t(const std::string &t)
    : base_t()
    , text(t)
  {
  }

  virtual void print()
  {
    std::cout << "public_inh_t::print() -> " << text << std::endl;
  }
};

struct private_inh_t : base_t {
  std::string text;

  private_inh_t(const std::string &t)
    : base_t()
    , text(t)
  {
  }

  virtual void print()
  {
    std::cout << "private_inh_t::print() -> " << text << std::endl;
  }
};

#define alloc new

#ifdef alloc
  #define deref ->
  #define value base_t *
#else
  #define alloc
  #define deref .
  #define value base_t
#endif

typedef value value_type;
typedef std::vector<value_type> base_v;

int main(int argc, char **argv)
{
  base_v _a;
  base_v _b;

  _a.push_back( alloc public_inh_t ("Hello, world!") );
  _a.push_back( alloc private_inh_t("Hello, world!") );
  
  for (value_type &v : _a)
    v deref print();

  _b = _a;

  for (value_type &v : _b)
    v deref print();
}
