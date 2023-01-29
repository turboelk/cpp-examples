#include <iostream>
#include <string>

struct object {
  int a, b;
};

int main(int argc, char **argv)
{
#define mem_size 1000
  int mem [mem_size];

  int *p = &mem[0];

  for (int i = 0; i < (mem_size / 2); ++i, ++p)
    *p = 0;

  for (int i = (mem_size / 2); i < mem_size; ++i, ++p)
    *p = 5;

  p = &mem[mem_size / 2];

  std::cout << std::to_string(*p) << ", " << std::to_string(p[-1]) << std::endl;
}
