#include <gtest/gtest.h>
#include "Vector.h"

TEST(Vector, Init) {
  Vector<int> vec;
  vec.set(1, 10);
  vec.set(4, 24);
  vec.set(3, 20);

}

