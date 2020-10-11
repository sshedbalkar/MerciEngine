#pragma once
#include "../common/exported.h"

/**
 * @brief Test class
 *
 */
class EXPORTED apiClass {
public:
  /**
   * @brief Default constructor
   *
   */
  apiClass();

  /**
   * @brief Destructor
   *
   */
  ~apiClass();

  /**
   * @brief Copy constructor
   *
   * @param other
   */
  apiClass(const apiClass &other);

  /**
   * @brief Copy assignment constructor
   *
   * @param other
   * @return apiClass&
   */
  apiClass &operator=(const apiClass &other);

  /**
   * @brief Move constructor
   *
   * @param other
   */
  apiClass(apiClass &&other) noexcept;

  /**
   * @brief Move assignment constructor
   *
   * @param other
   * @return apiClass&
   */
  apiClass &operator=(apiClass &&other) noexcept;

  /**
   * @brief Test api
   *
   * @param a
   * @param b
   * @return int
   */
  int add(int a, int b);
};