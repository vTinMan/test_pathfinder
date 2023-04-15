#include "common.hpp"

#include <forward_list>

#ifndef PATHFINDER_H_INCLUDED
#define PATHFINDER_H_INCLUDED

using FieldPath = std::forward_list<FieldPoint>;

class Pathfinder {
private:
  FieldSize size;
  FieldPoint start_point;
  FieldPoint end_point;
  FieldPath* found_path;
  FieldPoints* forbidden;
public:
  Pathfinder(FieldSize fsize, FieldPoint start_point, FieldPoint end_point, FieldPoints* forbidden);
  ~Pathfinder();
  bool find_shortest_path();
  void printintro();
  void print_output_graph();
  FieldPath* get_found_path();
};

#endif
