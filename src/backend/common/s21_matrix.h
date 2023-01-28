/*
 *   Copyright DATAN(c) 2023
 *   3DViewer_v1.0 made by bernardi, joaquind, stonehom, hazzeasu, killeral
 *   All rights reserved.
 */

#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum {
  OK = 0,
  INCORRECT_MATRIX = 1,
  CALC_ERROR = 2,
};

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

#endif  // SRC_S21_MATRIX_H_