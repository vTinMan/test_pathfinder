#include "pathfinder.hpp"
#include "findpath.h"

extern "C" CPath find_path(int size_x, int size_y, int start_x, int start_y, int end_x, int end_y, CPath* locked_points)
{
  FieldPoints forbidden;
  for(int i=0; i < locked_points->path_length; i++) {
    int x = locked_points->points[i].x;
    int y = locked_points->points[i].y;
    forbidden.push_front(FieldPoint(x, y));
  }

  Pathfinder my_finder(FieldSize(size_x, size_y),
                       FieldPoint(start_x, start_y),
                       FieldPoint(end_x, end_y),
                       &forbidden);
  my_finder.find_shortest_path();

  FieldPath* path = my_finder.get_found_path();
  int path_length = std::distance(path->begin(), path->end());
  CFieldPoint* points = new CFieldPoint[path_length];
  int i=0;
  for (auto point=path->begin(); point!=path->end(); point++, i++)
  {
    points[i].x = point->x();
    points[i].y = point->y();
  }
  CPath result_path;
  result_path.path_length = path_length;
  result_path.points = points;
  return result_path;
}

extern "C" void print_path(int size_x, int size_y, int start_x, int start_y, int end_x, int end_y, CPath* locked_points)
{
  FieldPoints forbidden;
  for(int i=0; i < locked_points->path_length; i++) {
    int x = locked_points->points[i].x;
    int y = locked_points->points[i].y;
    forbidden.push_front(FieldPoint(x, y));
  }

  Pathfinder my_finder(FieldSize(size_x, size_y),
                       FieldPoint(start_x, start_y),
                       FieldPoint(end_x, end_y),
                       &forbidden);
  my_finder.find_shortest_path();
  my_finder.printintro();
  my_finder.print_output_graph();
}
