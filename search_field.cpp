#include "search_field.hpp"

Direction calc_step_direction(PathStep* s1)
{
  PathStep* s0 = s1->previous();
  return (s0 == NULL) ? Direction(0,0) : Direction(s1->x() - s0->x(), s1->y() - s0->y());
}

bool compare_directions(Direction* d1, Direction* d2)
{
  return d1->x() == d2->x() && d1->y() == d2->y();
}

SearchField::SearchField(FieldSize field_size, FieldPoints* forbidden): size(field_size)
{
  this->line_size = this->size.x() * this->size.y();
  for(int i = 0; i < this->line_size; i++) {
    field_points.push_back(new FieldState());
  }
  for(auto point : *forbidden) {
    auto point_state = this->at(point.x(), point.y());
    if (point_state == NULL) { continue; }
    point_state->set_forbidden();
  }
  this->found_route = NULL;
};

SearchField::~SearchField()
{
  while(!backlog.empty()) {
    SearchRoute* search_route = backlog.front();
    while (!search_route->empty()) {
      PathStep* step = search_route->front();
      search_route->pop_front();
      delete step;
    }
    backlog.pop();
    delete search_route;
  }
  for(auto state : field_points)
    delete state;
}

bool SearchField::out_of_field(int x, int y) {
  if (x < 0 || y < 0)
    return true;
  if (this->size.x() <= x || this->size.y() <= y)
    return true;
  return false;
}

bool SearchField::out_of_field(FieldPoint* point) {
  return out_of_field(point->x(), point->y());
}

bool SearchField::out_of_route(FieldPoint* point)
{
  if (out_of_field(point))
    return true;
  if (this->at(point->x(), point->y())->is_forbidden())
    return true;
  return false;
}

FieldState* SearchField::at(int x, int y)
{
  if (out_of_field(x, y))
    return NULL;
  return this->field_points.at(x * this->size.x() + y);
}

FieldState* SearchField::at(FieldPoint* point)
{
  if (out_of_field(point))
    return NULL;
  return this->at(point->x(), point->y());
}

PathStep* SearchField::find_route(FieldPoint* start_point, FieldPoint* end_point)
{
  auto search_routes = new SearchRoute();
  search_routes->push_front(new PathStep(*start_point, NULL, 0));

  int max_length = this->size.x() * this->size.y();
  for (int _i = 0; _i < max_length; _i++) {
    this->backlog.push(search_routes);
    this->check_search_routes(search_routes, end_point);
    if(this->found_route != NULL) { return this->found_route; }
    search_routes = this->take_next_steps(search_routes);
  }
  return NULL;
}

SearchRoute* SearchField::take_next_steps(SearchRoute* search_routes)
{
  auto new_routes = new SearchRoute;
  for(PathStep* step : *search_routes) {
    for (auto dr : STEP_DIRECTIONS) {
      FieldPoint next_point(step->x() + dr.x(), step->y() + dr.y());
      if (this->out_of_route(&next_point)) { continue; };

      Direction old_dr = calc_step_direction(step);
      int complexity = step->get_complexity();
      if (!compare_directions(&dr, &old_dr)) { complexity++; }
      if (this->at(&next_point)->get_passed() < complexity) { continue; };

      auto new_step = new PathStep(next_point, step, complexity);
      this->at(&next_point)->set_passed(complexity);
      new_routes->push_front(new_step);
    }
  }
  return new_routes;
}

bool SearchField::check_search_routes(SearchRoute* new_routes, FieldPoint* end_point)
{
  for (auto step : *new_routes) {
    if (step->point()->x() == end_point->x() && step->point()->y() == end_point->y())
      if (this->found_route == NULL || this->found_route->get_complexity() > step->get_complexity())
        this->found_route = step;
  }
  return this->found_route;
}
