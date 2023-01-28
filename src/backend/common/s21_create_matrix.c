/*
 *   Copyright DATAN(c) 2023
 *   3DViewer_v1.0 made by bernardi, joaquind, stonehom, hazzeasu, killeral
 *   All rights reserved.
 */

#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (rows > 0 && columns > 0) {
    result->matrix = (double **)calloc(
        1, rows * sizeof(double *) + columns * rows * sizeof(double));
    if (result->matrix) {
      result->matrix[0] = (double *)(result->matrix + rows);
      for (int i = 1; i < rows; i++) {
        result->matrix[i] = result->matrix[0] + i * columns;
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  result->rows = rows;
  result->columns = columns;
  return res;
}
