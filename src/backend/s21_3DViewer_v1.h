/*
 *   Copyright DATAN(c) 2023
 *   3DViewer_v1.0 made by bernardi, joaquind, stonehom, hazzeasu, killeral
 *   All rights reserved.
 */

#ifndef S21_3DVIEWER_V1_H
#define S21_3DVIEWER_V1_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./common/s21_matrix.h"

#define S_SIZE 1024

typedef struct facets {
  unsigned int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
  int count_of_vertexes;
  int count_of_facets;
  double *massiv;
  double max_coord;
  matrix_t matrix_3d;
  polygon_t *polygons;
  unsigned int *massivPolygons;
  unsigned int sizePolygons;
  double *massiv_const;
} data_t;

int s21_parsing(data_t *data, char *model_file_name);
int s21_parsingDataSize(data_t *data, char *model_file_name);
int s21_parsingСonditions(char c, char *string_file, int *step);
void s21_remove_data(data_t *data);

int s21_findPolygons(polygon_t *polygons, char *string_file);
int s21_massivPolygons(data_t *data);
void s21_remove_polygons(data_t *data);

int s21_string_to_double(char *str, int *step, double *number);
int s21_Euler_search(char *str, int *step, double *num);

int s21_matrix_to_massiv(matrix_t matrix, double *massiv, double *massiv2);
void s21_remove_massiv(data_t *data);

int s21_skip_space(char *str, int *step);
int s21_is_space(char c);

int s21_num_digits(int num);
int s21_is_digit(char c);

void s21_array_minmax(data_t data, double *max_coord);

void s21_move_x(data_t *data, long double a_now, long double a_prev);
void s21_move_y(data_t *data, long double a_now, long double a_prev);
void s21_move_z(data_t *data, long double a_now, long double a_prev);

void s21_rotate_x(data_t *data, long double angle, long double angle_prev);
void s21_rotate_y(data_t *data, long double angle, long double angle_prev);
void s21_rotate_z(data_t *data, long double angle, long double angle_prev);
long double s21_degres_to_radians(long double angle);

void s21_scale(data_t *data, long double scale, long double scale_prev);

#endif
