#include <stdint.h>
#include <tr1/functional_hash.h>
#include <vector>

class count_min_sketch_base {
public:
  void add(uint32_t key, uint32_t value);
  uint32_t estimate(uint32_t key) const;
  count_min_sketch_base(int width, int height);
private:
  int width_; // actual width is (1 << width)
  int height_;

  std::vector<std::vector<uint32_t> > count_matrix_;
};

template<typename T, typename hash = std::tr1::hash<T> >
class count_min_sketch : private count_min_sketch_base {
private:
  using count_min_sketch_base::add;
  using count_min_sketch_base::estimate;
  count_min_sketch();
public:
  count_min_sketch(int width, int height)
    :count_min_sketch_base(width, height) {}

  void add(const T& key, int value){
    count_min_sketch_base::add(hash()(key), value);
  }
  int estimate(const T& key) const {
    return count_min_sketch_base::estimate(hash()(key));
  }
};

