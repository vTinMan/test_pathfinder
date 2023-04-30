#ifndef findpath_h__
#define findpath_h__

typedef struct field_point {
  int x;
  int y;
} CFieldPoint;

typedef struct field_path
{
  int path_length;
  CFieldPoint* points;
} CPath;

#ifdef __cplusplus
extern "C" {
#endif

CPath find_path(int size_x, int size_y, int start_x, int start_y, int end_x, int end_y, CPath* locked_points);
void print_path(int size_x, int size_y, int start_x, int start_y, int end_x, int end_y, CPath* locked_points);

#ifdef __cplusplus
}
#endif

#endif // findpath_h__
