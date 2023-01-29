#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cout << "usage: "
      << argv[0]
      << " <max length> [text]"
      << std::endl;

    return 1;
  }

  int max_length = 0;
  std::string text = "";

  try {
    max_length = std::stoi(argv[1]);
  }

  catch (std::invalid_argument e) {
    std::cout << "The max length must be of type integer" << std::endl;
    return 2;
  }

  for (int i = 2; i < argc; ++i)
    text += argv[i];

  int diff = text.size() - max_length;

  while(diff > 0) {
    text.pop_back();
    diff = text.size() - max_length;

    std::cout << diff << "\t" << text << std::endl;
  }

  std::cout << text << std::endl;
}
