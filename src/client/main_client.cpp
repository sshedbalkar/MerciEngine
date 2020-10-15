#include "../include/apiClass.h"
#include "../include/debugIntf.h"
#include <iostream>

void print(const char *msg) { std::cout << "Printing: " << msg << std::endl; }
int main() {
  registerDebugCallback(print);
  std::cout << "main_client" << std::endl;
  apiClass api;
  int c = api.add(11, 22);
  std::cout << "The sum is: " << c << std::endl;
  std::cout.flush();
  return 0;
}