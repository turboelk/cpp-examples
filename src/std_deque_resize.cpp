#include <iostream>
#include <string>
#include <exception>
#include <deque>

void print(const std::string &msg, const std::deque<int> &deque)
{
  std::cout << "\t" << msg << std::endl;
  for (int item: deque) {
    std::cout << std::to_string(item) << std::endl;
  }
  std::cout << std::endl;
}

int main(int argc, char **argv)
{
  std::string a = "Hello";
  std::string b = "World";

  std::deque<int> deque;
  deque.push_back(0);
  deque.push_back(1);
  deque.push_back(2);
  deque.push_back(3);
  deque.push_back(4);
  deque.push_front(10);

  print("Contents #1:", deque);

  deque.resize(3);

  print("Contents #2:", deque);

  deque.push_front(11);
  deque.resize(3);
  print("Contents #3:", deque);
  
  deque.push_front(12);
  deque.resize(3);
  print("Contents #4:", deque);
  
  deque.push_front(13);
  deque.resize(3);
  print("Contents #5:", deque);

}
