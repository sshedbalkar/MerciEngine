#pragma once
#include "../common/exported.h"

class EXPORTED apiClass {
public:
  apiClass();
  ~apiClass();
  apiClass(const apiClass &other);
  apiClass &operator=(const apiClass &other);
  apiClass(apiClass &&other) noexcept;
  apiClass &operator=(apiClass &&other) noexcept;
  int add(int a, int b);
};