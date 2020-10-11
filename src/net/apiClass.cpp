#include "../include/apiClass.h"
#include <iostream>
#include <iterator>
#include <tuple>

apiClass::apiClass() {
  std::cout << "apiClass: Default Constructor" << std::endl;
}

apiClass::~apiClass() { std::cout << "apiClass: Destructor" << std::endl; }

apiClass::apiClass(const apiClass &other) {
  std::cout << "apiClass: Copy Constructor" << std::endl;
  std::ignore = other;
}

apiClass &apiClass::operator=(const apiClass &other) {
  std::cout << "apiClass: Copy assignment operator" << std::endl;
  if (this != &other) {
  }
  return *this;
}

apiClass::apiClass(apiClass &&other) noexcept {
  std::cout << "apiClass: Move Constructor" << std::endl;
  std::ignore = other;
}

apiClass &apiClass::operator=(apiClass &&other) noexcept {
  std::cout << "apiClass: Move assignment operator" << std::endl;
  if (this != &other) {
  }
  return *this;
}

int apiClass::add(int a, int b) { return a + b; }