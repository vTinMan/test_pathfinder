#include "common.hpp"

#include <array>
#include <vector>
#include <queue>

#ifndef SEARCHFIELD_H_INCLUDED
#define SEARCHFIELD_H_INCLUDED

using Direction = AlgebraicPair;

const std::array<Direction, 4> STEP_DIRECTIONS{ { Direction(1,0), Direction(0,1), Direction(-1,0), Direction(0,-1) } };

class PathStep
{
  FieldPoint field_point;
  int complexity;
  PathStep* previous_step;
public:
  PathStep(FieldPoint field_point, PathStep* previous_step, int complexity):
      field_point(field_point), previous_step(previous_step), complexity(complexity) {};
  PathStep* previous() { return this->previous_step; }
  FieldPoint* point() { return &this->field_point; };
  int get_complexity() { return this->complexity; };
  int x() { return this->field_point.x(); };
  int y() { return this->field_point.y(); };
};

using SearchRoute = std::forward_list<PathStep*>;

class FieldState {
  unsigned int passed;
  char mark;
  bool forbidden;
public:
  FieldState() { this->passed = -1; this->mark = ' '; this->forbidden = false; };
  void set_passed(unsigned int passed) { this->passed = passed; };
  unsigned int get_passed() { return this->passed; };
  bool is_passed() { return this->passed == -1; };
  void set_forbidden() { this->forbidden = true; };
  bool is_forbidden() { return this->forbidden; };
  void set_mark(char new_mark) { this->mark = new_mark; };
  char get_mark() { return this->mark; };
};

class SearchField
{
  int line_size;
  FieldSize size;
  std::vector<FieldState*> field_points;
  std::queue<SearchRoute*> backlog;
  PathStep* found_route;
  bool check_search_routes(SearchRoute* new_routes, FieldPoint* end_point);
  bool out_of_field(int x, int y);
  bool out_of_field(FieldPoint* point);
  SearchRoute* take_next_steps(SearchRoute* search_routes);
public:
  SearchField(FieldSize field_size, FieldPoints* forbidden);
  ~SearchField();
  bool out_of_route(FieldPoint* point);
  PathStep* find_route(FieldPoint* start_point, FieldPoint* end_point);
  FieldState* at(int x, int y);
  FieldState* at(FieldPoint*);
};

#endif
