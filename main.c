#include "findpath.h"

int main(int argc, char* argv[]) {
  CFieldPoint points[30] = {
    {0, 6}, {1,  6}, {2,  6}, {3,  6},
    {4,  6}, {5,  6}, {6,  6}, {7,  6},
    {8,  6}, {9,  6}, {10, 6}, {11, 6},
    {12, 6}, {4,  14}, {5,  14}, {6,  14},
    {7,  14}, {8,  14}, {9,  14}, {10, 14},
    {11, 14}, {12, 14}, {13, 14}, {14, 14},
    {15, 14}, {16, 14}, {17, 14}, {18, 14},
    {19, 14}, {20, 14}
  };
  CPath cforbidden;
  cforbidden.path_length = sizeof(points)/sizeof(CFieldPoint);;
  cforbidden.points = &points[0];

  print_path(20, 20, 3, 2, 9, 17, &cforbidden);
  return 0;
}
