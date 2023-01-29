#include <iostream>
#include <string>
#include <exception>

int main(int argc, char **argv)
{
  std::string a = "Hello";
  std::string b = "World";

  std::cout << "pre: " << std::endl;
  std::cout << "\ta: " << a << std::endl;
  std::cout << "\tb: " << b << std::endl;

  std::swap(a, b);
  std::cout << "post: " << std::endl;
  std::cout << "\ta: " << a << std::endl;
  std::cout << "\tb: " << b << std::endl;
}
