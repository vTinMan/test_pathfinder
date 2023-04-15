#include <utility>
#include <forward_list>

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

class AlgebraicPair
{
  std::pair<int, int> data;
public:
  AlgebraicPair(int x, int y): data(std::pair<int, int>(x, y)) {};
  AlgebraicPair() {};
  std::pair<int, int> get_data() { return data; };
  int x() { return data.first; };
  int y() { return data.second; };
};

using FieldSize = AlgebraicPair;
using FieldPoint = AlgebraicPair;
using FieldPoints = std::forward_list<FieldPoint>;

#endif
