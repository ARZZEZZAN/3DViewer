#ifndef S21_3DVIEWER_V1_H
#define S21_3DVIEWER_V1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 1024

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

int s21_parsing(data_t *data, char *model_file_name);
int s21_parsingDataSize(data_t *data, char *model_file_name);
int s21_parsingСonditions(char c, char *string_file, int *step);

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

void s21_findPolygons(polygon_t *polygons, char *string_file);
void s21_remove_polygons(data_t data);
int s21_num_digits(int num);

int s21_string_to_double(char *str, int *step, double *number);
int s21_is_digit(char c);

int s21_skip_space(char *str, int *step);
int s21_is_space(char c);

void printf_matrix(matrix_t matrix);
void printf_polygons(data_t data);

#endif