#include <iostream>
#include "hoks.hpp"
#include "MurmurHash3.h"
#include <stdexcept>
#include <algorithm>

namespace detail {

inline size_t hash(uint32_t key, uint32_t seed) {
  uint32_t output = 0;
  MurmurHash3_x86_32(&key, sizeof(size_t), seed, &output);
  return output;
}

}

count_min_sketch_base::count_min_sketch_base(int width, int height)
  :width_(width), height_(height) {
  if (31 < width) {
    throw std::range_error("specified width is too wide");
  }
}

void count_min_sketch_base::add(uint32_t key, uint32_t value) {
  std::cout << "adding:" << key << " + " << value << std::endl;
  if (value == 0) { return; }
  if (count_matrix_.empty()) {
    for (int i = 0; i < height_; ++i) {
      count_matrix_.push_back(std::vector<uint32_t>(1 << width_, 0U));
    }
  }
  const uint32_t mask = (1LLU << width_) - 1;
  for (int i = 0; i < height_; ++i) {
    const uint32_t hashvalue = detail::hash(key, i) & mask;
    count_matrix_[i][hashvalue] += value;
    std::cout << "value[" << i << "][" << hashvalue << "]=" << count_matrix_[i][hashvalue] << std::endl;
  }
}

uint32_t count_min_sketch_base::estimate(uint32_t key) const {
  if (count_matrix_.empty()) { return 0; }
  const uint32_t mask = (1LLU << width_) - 1;
  uint32_t min = ~0;
  std::cout << "estimate:" << key << std::endl;
  for (int i = 0; i < height_; ++i) {
    const uint32_t hashvalue = detail::hash(key, i) & mask;
    std::cout << "value[" << i << "][" << hashvalue << "]=" << count_matrix_[i][hashvalue] << std::endl;
    min = std::min(min, count_matrix_[i][hashvalue]);
  }
  return min;
}
