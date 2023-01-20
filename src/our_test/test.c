#include <check.h>

#include "../s21_3DViewer_v1.h"

START_TEST(test_s21_parsing_1) {
  data_t data = {0};
  char model_file_name[] = "./our_test/objFiles/test.obj";
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
  char* model_file_name = "./our_test/objFiles/test.obj";
  int result = s21_parsing(&data, model_file_name);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(data.matrix_3d.rows, 9);
  ck_assert_int_eq(data.matrix_3d.cols, 3);
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
  char model_file_name[] = "./our_test/objFiles/city.obj";
  // create test_model.txt file with some test data
  int result = s21_parsing(&data, model_file_name);
  ck_assert_int_eq(result, 1);
  // check that data.count_of_vertexes is correct
  ck_assert_int_eq(data.count_of_vertexes, 130930);
  // check that data.count_of_facets is correct
  ck_assert_int_eq(data.count_of_facets, 99708);
  // check that data.matrix_3d is correct
  // check that data.polygons is correct
  // check that data.massiv is correct
  // free memory
  s21_remove_data(&data);
}
END_TEST
START_TEST(test_s21_parsing_3) {
  data_t data = {0};
  char model_file_name[] = "./our_test/objFiles/pyramid.obj";
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
  char* model_file_name = "./our_test/objFiles/pyramid.obj";
  s21_parsing(&data, model_file_name);
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
  char model_file_name[] = "./our_test/objFiles/nothing.obj";
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
  char model_file_name[] = "./our_test/objFiles/davlnvd.txt";
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
  char model_file_name[] = "./our_test/objFiles/text.txt";
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

  srunner_run_all(sr, CK_ENV);
  wtf = srunner_ntests_failed(sr);

  srunner_free(sr);
  return wtf == 0 ? 0 : 1;
}
