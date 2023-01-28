/*
 *   Copyright DATAN(c) 2023
 *   3DViewer_v1.0 made by bernardi, joaquind, stonehom, hazzeasu, killeral
 *   All rights reserved.
 */

#include "./common/s21_matrix.h"
#include "s21_3DViewer_v1.h"
#include "string.h"

void s21_move_x(data_t *data, long double a_now, long double a_prev) {
  for (int i = 0; data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    data->massiv[i] += (a_now - a_prev);
  }
}

void s21_move_y(data_t *data, long double a_now, long double a_prev) {
  for (int i = 1; data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    data->massiv[i] += (a_now - a_prev);
  }
}

void s21_move_z(data_t *data, long double a_now, long double a_prev) {
  for (int i = 2; data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    data->massiv[i] += (a_now - a_prev);
  }
}

void s21_rotate_x(data_t *data, long double angle, long double angle_prev) {
  angle = s21_degres_to_radians(angle);
  angle_prev = s21_degres_to_radians(angle_prev);
  for (int i = 0; data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    long double y = data->massiv[i + 1];
    long double z = data->massiv[i + 2];

    // x'=x;
    // y':=y*cos(L)+z*sin(L) ;
    // z':=-y*sin(L)+z*cos(L) ;

    data->massiv[i + 1] =
        y * cosl(angle - angle_prev) + z * sinl(angle - angle_prev);
    data->massiv[i + 2] =
        -y * sinl(angle - angle_prev) + z * cosl(angle - angle_prev);
  }
}

void s21_rotate_y(data_t *data, long double angle, long double angle_prev) {
  angle = s21_degres_to_radians(angle);
  angle_prev = s21_degres_to_radians(angle_prev);
  for (int i = 0;
       data->massiv && data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    long double x = data->massiv[i];
    long double z = data->massiv[i + 2];

    // x'=x*cos(L)+z*sin(L);
    // y'=y;
    // z'=-x*sin(L)+z*cos(L);

    data->massiv[i] =
        x * cosl(angle - angle_prev) + z * sinl(angle - angle_prev);
    data->massiv[i + 2] =
        -x * sinl(angle - angle_prev) + z * cosl(angle - angle_prev);
  }
}

void s21_rotate_z(data_t *data, long double angle, long double angle_prev) {
  angle = s21_degres_to_radians(angle);
  angle_prev = s21_degres_to_radians(angle_prev);
  for (int i = 0; data->massiv && i < (data->count_of_vertexes + 1) * 3;
       i += 3) {
    long double x = data->massiv[i];
    long double y = data->massiv[i + 1];

    // x'=x*cos(L)-y*sin(L);
    // y'=x*sin(L)+y*cos(L);
    // z'=z;

    data->massiv[i] =
        x * cosl(angle - angle_prev) - y * sinl(angle - angle_prev);
    data->massiv[i + 1] =
        x * sinl(angle - angle_prev) + y * cosl(angle - angle_prev);
  }
}

long double s21_degres_to_radians(long double angle) {
  return angle * M_PI / 180.0;
}

void s21_scale(data_t *data, long double scale, long double scale_prev) {
  for (int i = 0; data->massiv && i < (data->count_of_vertexes + 1) * 3; i++) {
    data->massiv[i] *= scale / scale_prev;
  }
}
