/*
 *   Copyright DATAN(c) 2023
 *   3DViewer_v1.0 made by bernardi, joaquind, stonehom, hazzeasu, killeral
 *   All rights reserved.
 */

#include <check.h>
#include <math.h>

#include "../s21_3DViewer_v1.h"

START_TEST(test_s21_parsing_1) {
  data_t data = {0};
  char model_file_name[] = "./objFiles/test.obj";
  // create test_model.txt file with some test data
  int result = s21_parsing(&data, model_file_name);
  // printf("%lf\n", data.matrix_3d.matrix[1][0]);
  ck_assert_int_eq(result, 1);
  // check that data.count_of_vertexes is correct
  ck_assert_int_eq(data.count_of_vertexes, 8);
  // check that data.count_of_facets is correct
  ck_assert_int_eq(data.count_of_facets, 12);
  // check that data.matrix_3d is correct
  // check that data.polygons is correct
  // check that data.massiv is correct
  // free memory
  s21_remove_data(&data);
}
END_TEST

START_TEST(test_s21_parsing_matrix) {
  data_t data = {0};
  char* model_file_name = "./objFiles/test.obj";
  int result = s21_parsing(&data, model_file_name);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(data.matrix_3d.rows, 9);
  ck_assert_int_eq(data.matrix_3d.columns, 3);
  ck_assert_double_eq(data.matrix_3d.matrix[1][0], 0.0);
  ck_assert_double_eq(data.matrix_3d.matrix[1][1], 0.0);
  ck_assert_double_eq(data.matrix_3d.matrix[1][2], 0.0);
  ck_assert_double_eq(data.matrix_3d.matrix[8][0], 1.0);
  ck_assert_double_eq(data.matrix_3d.matrix[8][1], 1.0);
  ck_assert_ldouble_eq_tol(data.matrix_3d.matrix[8][2], 1e-07, 1e-07);
  s21_remove_data(&data);
}
END_TEST

START_TEST(test_s21_parsing_2) {
  data_t data = {0};
  char* model_file_name = "./objFiles/city.obj";
  // create test_model.txt file with some test data
  int result = s21_parsing(&data, model_file_name);
  ck_assert_int_eq(result, 0);
  s21_remove_data(&data);
}
END_TEST
START_TEST(test_s21_parsing_3) {
  data_t data = {0};
  char model_file_name[] = "./objFiles/pyramid.obj";
  // create test_model.txt file with some test data
  int result = s21_parsing(&data, model_file_name);
  ck_assert_int_eq(result, 1);
  // check that data.count_of_vertexes is correct
  ck_assert_int_eq(data.count_of_vertexes, 5);
  // check that data.count_of_facets is correct
  ck_assert_int_eq(data.count_of_facets, 6);
  // check that data.matrix_3d is correct
  // check that data.polygons is correct
  // check that data.massiv is correct
  // free memory
  s21_remove_data(&data);
}
END_TEST

START_TEST(test_first_vertex) {
  data_t data = {0};
  char* model_file_name = "./objFiles/pyramid.obj";
  int result = s21_parsing(&data, model_file_name);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(data.matrix_3d.matrix[1][0], 0.0, 1e-7);
  ck_assert_double_eq_tol(data.matrix_3d.matrix[1][1], 1.0, 1e-7);
  ck_assert_double_eq_tol(data.matrix_3d.matrix[1][2], 0.0, 1e-7);
  s21_remove_data(&data);
}
END_TEST
START_TEST(test_s21_parsing_4) {
  data_t data = {0};
  char model_file_name[] = "./objFiles/nothing.obj";
  // create test_model.txt file with some test data
  int result = s21_parsing(&data, model_file_name);
  ck_assert_int_eq(result, 1);
  // check that data.matrix_3d is correct
  // check that data.polygons is correct
  // check that data.massiv is correct
  // free memory
  s21_remove_data(&data);
}
END_TEST

START_TEST(test_s21_parsing_6) {
  data_t data = {0};
  char model_file_name[] = "./objFiles/davlnvd.txt";
  // create test_model.txt file with some test data
  int result = s21_parsing(&data, model_file_name);
  ck_assert_int_eq(result, 0);
  // check that data.matrix_3d is correct
  // check that data.polygons is correct
  // check that data.massiv is correct
  // free memory
  s21_remove_data(&data);
}
END_TEST
START_TEST(test_s21_parsing_7) {
  data_t data = {0};
  char model_file_name[] = "./objFiles/text.txt";
  // create test_model.txt file with some test data
  int result = s21_parsing(&data, model_file_name);
  ck_assert_int_eq(result, 1);
  // check that data.matrix_3d is correct
  // check that data.polygons is correct
  // check that data.massiv is correct
  // free memory
  s21_remove_data(&data);
}
END_TEST

START_TEST(test_s21_move_x_1) {
  data_t data;
  memset(&data, 0, sizeof(data_t));
  int result = s21_parsing(&data, "./objFiles/pyramid.obj");
  ck_assert_int_eq(result, 1);
  double prev_x = data.massiv[0];
  s21_move_x(&data, 1.0, 0.0);
  ck_assert_double_eq(data.massiv[0], prev_x + 1.0);
  s21_remove_data(&data);
}
END_TEST
START_TEST(test_s21_move_y_1) {
  data_t data;
  memset(&data, 0, sizeof(data_t));
  int result = s21_parsing(&data, "./objFiles/pyramid.obj");
  ck_assert_int_eq(result, 1);
  double prev_y = data.massiv[1];
  s21_move_y(&data, 1.0, 0.0);
  ck_assert_double_eq(data.massiv[1], prev_y + 1.0);
  s21_remove_data(&data);
}
END_TEST
START_TEST(test_s21_move_z_1) {
  data_t data;
  memset(&data, 0, sizeof(data_t));
  int result = s21_parsing(&data, "./objFiles/pyramid.obj");
  ck_assert_int_eq(result, 1);
  double prev_z = data.massiv[2];
  s21_move_z(&data, 1.0, 0.0);
  ck_assert_double_eq(data.massiv[2], prev_z + 1.0);
  s21_remove_data(&data);
}
END_TEST

START_TEST(test_s21_rotate_x) {
  data_t data = {0};
  data.count_of_vertexes = 7;
  double massiv[] = {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
                     0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0,
                     0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  data.massiv = massiv;

  s21_rotate_x(&data, 45.0, 0.0);

  // Checking if x value of vertexes hasn't changed
  for (int i = 0; i < (data.count_of_vertexes + 1) * 3; i += 3)
    ck_assert_double_eq_tol(data.massiv[i], massiv[i], 0.0001);

  // Checking if y and z values of vertex 1 has changed
  ck_assert_double_eq_tol(data.massiv[1], 0.0, 0.0001);
  ck_assert_double_eq_tol(data.massiv[2], 0.0, 0.0001);
}
END_TEST

START_TEST(test_s21_rotate_y_1) {
  data_t data = {0};
  double angle = 1, angle_prev = 0;
  s21_rotate_y(&data, angle, angle_prev);
  for (int i = 0; i < data.count_of_vertexes; i++) {
    double x = data.matrix_3d.matrix[i][0];
    double z = data.matrix_3d.matrix[i][2];
    ck_assert(fabs(x - (double)cos(angle - angle_prev)) < 0.001);
    ck_assert(fabs(z + (double)sin(angle - angle_prev)) < 0.001);
  }
}
END_TEST

START_TEST(test_s21_rotate_z_1) {
  data_t data = {0};
  memset(&data, 0, sizeof(data_t));
  data.count_of_vertexes = 1;
  data.massiv = (double*)calloc(6, sizeof(double));
  data.massiv[3] = 1.0;
  data.massiv[4] = 2.0;
  data.massiv[5] = 3.0;
  s21_rotate_z(&data, 45.0, 0.0);
  ck_assert_double_eq_tol(data.massiv[3], -(sqrt(2) / 2), 0.0001);
  ck_assert_double_eq_tol(data.massiv[4], 3 * (sqrt(2) / 2), 0.0001);
  ck_assert_double_eq_tol(data.massiv[5], 3.0, 0.0001);
  free(data.massiv);
}
END_TEST

START_TEST(test_s21_rotate_z_2) {
  data_t data;
  memset(&data, 0, sizeof(data_t));
  data.count_of_vertexes = 1;
  data.massiv = (double*)calloc(6, sizeof(double));
  data.massiv[3] = 1.0;
  data.massiv[4] = 2.0;
  data.massiv[5] = 3.0;
  s21_rotate_z(&data, 90.0, 45.0);
  ck_assert_double_eq_tol(data.massiv[3], -(sqrt(2) / 2), 0.0001);
  ck_assert_double_eq_tol(data.massiv[4], 3 * (sqrt(2) / 2), 0.0001);
  free(data.massiv);
}
END_TEST
START_TEST(test_s21_rotate_y_3) {
  data_t data;
  memset(&data, 0, sizeof(data_t));
  data.count_of_vertexes = 1;
  data.massiv = (double*)calloc(6, sizeof(double));
  data.massiv[3] = 1.0;
  data.massiv[4] = 2.0;
  data.massiv[5] = 3.0;
  s21_rotate_y(&data, 90.0, 45.0);
  ck_assert_double_eq_tol(data.massiv[3], 2.82843, 0.0001);
  ck_assert_double_eq_tol(data.massiv[4], 2, 0.0001);
  free(data.massiv);
}
END_TEST
START_TEST(test_s21_scale_1) {
  data_t data = {0};
  data.count_of_vertexes = 4;
  data.massiv = (double*)malloc(15 * sizeof(double));
  data.massiv[0] = 4;
  data.massiv[1] = -5;
  data.massiv[2] = 6;
  data.massiv[3] = 7;
  data.massiv[4] = -8;
  data.massiv[5] = 9;
  data.massiv[6] = 0;
  data.massiv[7] = 1;
  data.massiv[8] = -2;
  data.massiv[9] = -3;
  data.massiv[10] = 4;
  data.massiv[11] = -5;
  s21_scale(&data, 2, 1);
  double result[12] = {8, -10, 12, 14, -16, 18, 0, 2, -4, -6, 8, -10};

  ck_assert_double_eq(data.massiv[0], result[0]);
  ck_assert_double_eq(data.massiv[1], result[1]);
  ck_assert_double_eq(data.massiv[2], result[2]);
  ck_assert_double_eq(data.massiv[3], result[3]);
  ck_assert_double_eq(data.massiv[4], result[4]);
  ck_assert_double_eq(data.massiv[5], result[5]);
  free(data.massiv);
}
END_TEST
int main(void) {
  Suite* s1 = suite_create("s21_parser");
  TCase* test_case_1 = tcase_create("s21_parser");
  SRunner* sr = srunner_create(s1);
  int wtf;
  suite_add_tcase(s1, test_case_1);

  tcase_add_test(test_case_1, test_s21_parsing_1);
  tcase_add_test(test_case_1, test_s21_parsing_matrix);

  tcase_add_test(test_case_1, test_s21_parsing_2);

  tcase_add_test(test_case_1, test_s21_parsing_3);
  tcase_add_test(test_case_1, test_first_vertex);

  tcase_add_test(test_case_1, test_s21_parsing_4);
  tcase_add_test(test_case_1, test_s21_parsing_6);
  tcase_add_test(test_case_1, test_s21_parsing_7);

  tcase_add_test(test_case_1, test_s21_move_x_1);
  tcase_add_test(test_case_1, test_s21_move_y_1);
  tcase_add_test(test_case_1, test_s21_move_z_1);

  tcase_add_test(test_case_1, test_s21_rotate_x);
  tcase_add_test(test_case_1, test_s21_rotate_y_1);
  tcase_add_test(test_case_1, test_s21_rotate_y_3);
  tcase_add_test(test_case_1, test_s21_rotate_z_1);
  tcase_add_test(test_case_1, test_s21_rotate_z_2);
  tcase_add_test(test_case_1, test_s21_scale_1);

  srunner_run_all(sr, CK_ENV);
  wtf = srunner_ntests_failed(sr);

  srunner_free(sr);
  return wtf == 0 ? 0 : 1;
}
