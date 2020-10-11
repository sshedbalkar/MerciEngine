#include "../include/apiClass.h"
#include <iostream>

int main() {
  std::cout << "main_client" << std::endl;
  apiClass api;
  int c = api.add(11, 22);
  std::cout << "The sum is: " << c << std::endl;
}