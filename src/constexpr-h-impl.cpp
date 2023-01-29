#include "constexpr-h-decl.hpp"

#include <string>
#include <iostream>

Type(Integer, int);
Type(Date, int);
Type(Varchar, std::string);

Type(Hello, \
    Type(World, std::string));

int main(int, char **)
{
  std::cout << Varchar::name << std::endl;
  std::cout << Date::name << std::endl;
  std::cout << Integer::name << std::endl;
  std::cout << Hello::name << ", "
   << Hello::type::name 
   << "!"
   << std::endl;
}
