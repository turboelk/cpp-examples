#include <iostream>
#include <string>
#include <exception>

void noop()
{
}

#define do try
#define while(x) catch(x) {}
#define you std::exception 

int main(int argc, char **argv)
{
  do {
    std::cout << "Hello, world!" << std::endl;
    throw std::runtime_error("CATCH ME IF YOU CAN");
  } 
  while(you can);
}
