#include "pathfinder.hpp"
#include "search_field.hpp"

#include <iostream>

Pathfinder::Pathfinder(FieldSize fsize, FieldPoint start_point, FieldPoint end_point, FieldPoints* forbidden)
{
  this->found_path = NULL;
  this->size = fsize;
  this->start_point = start_point;
  this->end_point = end_point;
  this->forbidden = forbidden;
}

Pathfinder::~Pathfinder()
{
  if (this->found_path != NULL) { delete this->found_path; }
}

void Pathfinder::printintro()
{
  std::cout << "field size: " << this->size.x() << "," << this->size.y() << std::endl;
  std::cout << "start position: " << this->start_point.x() << "," << this->start_point.y() << std::endl;
  std::cout << "end position: " << this->end_point.x() << "," << this->end_point.y() << std::endl;
}

bool Pathfinder::find_shortest_path()
{
  SearchField search_field(this->size, this->forbidden);
  PathStep* step = search_field.find_route(&this->start_point, &this->end_point);
  if (step == NULL) { return false; }

  this->found_path = new FieldPath();
  do {
    this->found_path->push_front(*step->point());
  } while(step = step->previous());
  return true;
}

void Pathfinder::print_output_graph()
{
  SearchField out_field(this->size, this->forbidden);
  std::cout << std::endl << "found path:" << std::endl;
  for (auto point : *found_path) {
    std::cout << point.x() << "," << point.y() << " ;  ";
    out_field.at(point.x(), point.y())->set_mark(':');
  }
  out_field.at(start_point.x(), start_point.y())->set_mark('S');
  out_field.at(end_point.x(), end_point.y())->set_mark('X');

  std::cout << std::endl << std::endl;
  for(int cj=0; cj<size.y()+2; cj++) {
    for(int ci=0; ci<size.x()+2; ci++) {
      int x = ci - 1;
      int y = cj - 1;
      if (ci == 0 || cj == 0 || x == size.x() || y == size.y() || out_field.at(x, y)->is_forbidden()) {
        std::cout << '#' << '#';
      } else {
        std::cout << out_field.at(x, y)->get_mark() << out_field.at(x, y)->get_mark();
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

FieldPath* Pathfinder::get_found_path() {
  return this->found_path;
}