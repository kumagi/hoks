#include <iostream>
#include <gtest/gtest.h>
#include <string>

#include "hoks.hpp"

TEST(minsketch,construct) {
  count_min_sketch<int> i(1,2);
  count_min_sketch<char> c(2,3);
  count_min_sketch<std::string> s(2,4);
  count_min_sketch<float> f(4,5);
  count_min_sketch<bool> b(3,1);
}

TEST(minsketch,add) {
  count_min_sketch<int> i(1,2);
  i.add(2, 21);
}

TEST(minsketch,estimate) {
  count_min_sketch<int> i(1,2);
  i.add(2, 21);
  ASSERT_EQ(21, i.estimate(2));
}

TEST(minsketch,multi_estimate) {
  count_min_sketch<int> s(12,8);
  for(int i = 0; i<1000; ++i) {
    s.add(i, i*i);
  }
  for(int i = 0; i<1000; ++i) {
    std::cerr << "v:" << i << std::endl;
    ASSERT_EQ(i*i, s.estimate(i));
  }
}
