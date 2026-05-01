#include <iostream>
#include <map>
#include <deque>

int main() {
  std::map<int, std::string> myMap;
  myMap[1] = "Hello";
  myMap[2] = "World";

  // Get the iterator to the first element
  auto it = myMap.begin();

  std::cout << "Pointer" << &(*it) << std::endl;

  // Move the iterator to the second element
  it++;

  std::cout << "Pointer" << &(*it) << std::endl;

  return 0;
}
