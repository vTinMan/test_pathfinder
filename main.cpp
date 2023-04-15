#include <cstdlib>
#include "pathfinder.hpp"

int main(int argc, char* argv[]) {
  FieldPoints forbidden;
  forbidden.push_front(FieldPoint(0,  6));
  forbidden.push_front(FieldPoint(1,  6));
  forbidden.push_front(FieldPoint(2,  6));
  forbidden.push_front(FieldPoint(3,  6));
  forbidden.push_front(FieldPoint(4,  6));
  forbidden.push_front(FieldPoint(5,  6));
  forbidden.push_front(FieldPoint(6,  6));
  forbidden.push_front(FieldPoint(7,  6));
  forbidden.push_front(FieldPoint(8,  6));
  forbidden.push_front(FieldPoint(9,  6));
  forbidden.push_front(FieldPoint(10, 6));
  forbidden.push_front(FieldPoint(11, 6));
  forbidden.push_front(FieldPoint(12, 6));

  forbidden.push_front(FieldPoint(4,  14));
  forbidden.push_front(FieldPoint(5,  14));
  forbidden.push_front(FieldPoint(6,  14));
  forbidden.push_front(FieldPoint(7,  14));
  forbidden.push_front(FieldPoint(8,  14));
  forbidden.push_front(FieldPoint(9,  14));
  forbidden.push_front(FieldPoint(10, 14));
  forbidden.push_front(FieldPoint(11, 14));
  forbidden.push_front(FieldPoint(12, 14));
  forbidden.push_front(FieldPoint(13, 14));
  forbidden.push_front(FieldPoint(14, 14));
  forbidden.push_front(FieldPoint(15, 14));
  forbidden.push_front(FieldPoint(16, 14));
  forbidden.push_front(FieldPoint(17, 14));
  forbidden.push_front(FieldPoint(18, 14));
  forbidden.push_front(FieldPoint(19, 14));

  Pathfinder my_finder(FieldSize(20, 20), FieldPoint(3, 2), FieldPoint(8, 18), &forbidden);
  my_finder.printintro();
  my_finder.find_shortest_path();
  my_finder.print_output_graph();
  return EXIT_SUCCESS;
}
