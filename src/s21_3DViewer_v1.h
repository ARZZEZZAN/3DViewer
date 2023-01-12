#ifndef S21_3DVIEWER_V1_H
#define S21_3DVIEWER_V1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Matrix {
  double **matrix;
  int rows;
  int cols;
} matrix_t;

typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
  int count_of_vertexes;
  int count_of_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
} data_t;

#endif