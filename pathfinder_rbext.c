#include <ruby.h>
#include <stdio.h>
#include "findpath.h"

VALUE mPathfinder;

VALUE rb_findpath(VALUE self,
                  VALUE size_x,  VALUE size_y,
                  VALUE start_x, VALUE start_y,
                  VALUE end_x,   VALUE end_y,
                  VALUE forbidden)
{
  CPath cforbidden;
  cforbidden.path_length = RARRAY_LEN(forbidden);
  cforbidden.points = calloc(cforbidden.path_length, sizeof(CFieldPoint));
  for(int i=0; i < cforbidden.path_length; i++) {
    VALUE point = rb_ary_entry(forbidden, i);
    cforbidden.points[i].x = NUM2INT(rb_ary_entry(point, 0));
    cforbidden.points[i].y = NUM2INT(rb_ary_entry(point, 1));
  }

  CPath path = find_path(FIX2INT(size_x), FIX2INT(size_y),
                         FIX2INT(start_x), FIX2INT(start_y),
                         FIX2INT(end_x), FIX2INT(end_y),
                         &cforbidden);

  VALUE res = rb_ary_new();
  for (int i = 0; i < path.path_length; i++) {
    VALUE val_x = INT2NUM(path.points[i].x);
    VALUE val_y = INT2NUM(path.points[i].y);
    VALUE internal_arr = rb_ary_new();
    rb_ary_push(internal_arr, val_x);
    rb_ary_push(internal_arr, val_y);
    rb_ary_push(res, internal_arr);
  }
  free(path.points);
  free(cforbidden.points);
  return res;
}

void Init_pathfinder_ext()
{
  mPathfinder = rb_define_module("Pathfinder");
  rb_define_singleton_method(mPathfinder, "findpath", rb_findpath, 7);
}
